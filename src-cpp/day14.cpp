#include "inputData.h"
#include <vector>
#include <set>
#include <sstream>
#include <iostream>
#include <fstream>

#define WIDTH 101
#define HEIGHT 103

int calcSafety(const std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>>& robots) {
    int quad1 = 0, quad2 = 0, quad3 = 0, quad4 = 0;

    for (const auto& [pos, vel] : robots) {
        const int x = pos.first;
        const int y = pos.second;

        if (x < WIDTH / 2 && y < HEIGHT / 2)
            quad1++;
        else if (x > WIDTH / 2 && y < HEIGHT / 2)
            quad2++;
        else if (x < WIDTH / 2 && y > HEIGHT / 2)
            quad3++;
        else if (x > WIDTH / 2 && y > HEIGHT / 2)
            quad4++;
    }

    return quad1 * quad2 * quad3 * quad4;
}

void printRobotsToFile(const std::set<std::pair<int, int>>& positions, std::ofstream& outFile, int t) {
    outFile << "Time step: " << t << "\n";
    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            if (positions.find({x, y}) != positions.end()) {
                outFile << '#';
            } else {
                outFile << '.';
            }
        }
        outFile << "\n";
    }
}

int main() {
    std::stringstream file = readInputData(14);

    std::string line;
    std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> robots;

    while (std::getline(file, line)) {
        std::pair pos{-1, -1};
        std::pair vel{-1, -1};
        for (int i = 0; i < line.size(); i++) {
            if (line[i] == '=') {
                int size = 0;
                while (line[i + size + 1] != ',')
                    size++;

                if (pos.first == -1)
                    pos.first = std::stoi(line.substr(i + 1, size));
                else
                    vel.first = std::stoi(line.substr(i + 1, size));
            }
            if (line[i] == ',') {
                int size = 0;
                while (isdigit(line[i + size + 1]) || line[i + size + 1] == '-')
                    size++;

                if (pos.second == -1)
                    pos.second = std::stoi(line.substr(i + 1, size));
                else
                    vel.second = std::stoi(line.substr(i + 1, size));
            }
        }
        robots.emplace_back(pos, vel);
    }

    for (int t = 1; t <= 12000; ++t) {

        // Update robot positions
        for (auto& [pos, vel] : robots) {
            pos.first = (pos.first + vel.first) % WIDTH;
            if (pos.first < 0) pos.first += WIDTH;

            pos.second = (pos.second + vel.second) % HEIGHT;
            if (pos.second < 0) pos.second += HEIGHT;
        }

        std::set<std::pair<int, int>> positions;
        bool overlap = false;
        for (const auto& [pos, vel] : robots) {
            if(!positions.insert(pos).second) {
                overlap = true;
            }
        }

        if (!overlap) {
            std::cout << "Potential Christmas Tree at " << t << std::endl;
            std::string filename = "./day14/sec";
            filename += std::to_string(t) + ".txt";
            std::ofstream output(filename);
            printRobotsToFile(positions,output,t);
            std::cout << "Outputted to " << filename << std::endl;
        }

        if(t == 100) {
            std::cout << "Safety factor after 100 seconds: " << calcSafety(robots) << std::endl;
        }

    }

    return EXIT_SUCCESS;
}
