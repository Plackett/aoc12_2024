#include <map>
#include <vector>
#include <algorithm>
#include <chrono>
#include <cmath>
#include <iostream>
#include <sstream>
#include <set>
#include "inputData.h"

struct vec2 {
    int x, y;
    const bool operator==(const vec2& other) const {
        return x == other.x && y == other.y;
    }
    bool operator<(const vec2& other) const {
        return std::tie(x, y) < std::tie(other.x, other.y);
    }
};

int main() {
    auto t1 = std::chrono::high_resolution_clock::now();
    std::stringstream file = readInputData(8);
    std::map<char, std::vector<vec2>> antennas{};
    std::set<vec2> directAntinodes;
    std::set<vec2> harmonicAntinodes;
    std::string line;
    int lineCount = 0;
    int horzSize = 0;

    while (std::getline(file, line)) {
        for (int i = 0; i < line.size(); i++) {
            if (line[i] != '.') {
                antennas[line[i]].push_back(vec2{i, lineCount});
            }
        }
        horzSize = line.size();
        lineCount++;
    }

    for (const auto& group : antennas) {
        const auto& positions = group.second;
        for (size_t i = 0; i < positions.size(); i++) {
            for (size_t j = 0; j < positions.size(); j++) {
                if (i == j) continue;

                vec2 a = positions[i];
                vec2 b = positions[j];

                int dx = b.x - a.x;
                int dy = b.y - a.y;

                vec2 candidateOne{a.x - dx, a.y - dy};
                vec2 candidateTwo{b.x + dx, b.y + dy};

                if (candidateOne.x >= 0 && candidateOne.y >= 0 && candidateOne.x < horzSize && candidateOne.y < lineCount) {
                    directAntinodes.insert(candidateOne);
                }
                if (candidateTwo.x >= 0 && candidateTwo.y >= 0 && candidateTwo.x < horzSize && candidateTwo.y < lineCount) {
                    directAntinodes.insert(candidateTwo);
                }

                vec2 extendedOne = candidateOne;
                vec2 extendedTwo = candidateTwo;

                harmonicAntinodes.insert(a);
                harmonicAntinodes.insert(b);

                while (true) {
                    extendedOne.x -= dx;
                    extendedOne.y -= dy;
                    if (extendedOne.x < 0 || extendedOne.y < 0 || extendedOne.x >= horzSize || extendedOne.y >= lineCount) break;
                    harmonicAntinodes.insert(extendedOne);
                }

                while (true) {
                    extendedTwo.x += dx;
                    extendedTwo.y += dy;
                    if (extendedTwo.x < 0 || extendedTwo.y < 0 || extendedTwo.x >= horzSize || extendedTwo.y >= lineCount) break;
                    harmonicAntinodes.insert(extendedTwo);
                }
            }
        }
    }

    harmonicAntinodes.insert(directAntinodes.begin(), directAntinodes.end());

    std::cout << "Number of direct antinodes: " << directAntinodes.size() << std::endl;
    std::cout << "Number of harmonic antinodes (including direct): " << harmonicAntinodes.size() << std::endl;
    auto t2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> ms_int = t2 - t1;
    std::cout << "elapsed time: " << ms_int.count() << " s" << std::endl;
    return EXIT_SUCCESS;
}
