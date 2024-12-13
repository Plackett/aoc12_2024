#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <tuple>
#include <cctype>
#include <cmath>

#include "inputData.h"

struct CoordinatePair {
    long long x;
    long long y;
};

std::tuple<CoordinatePair, CoordinatePair, CoordinatePair> extractData(const std::vector<std::string>& inputGroup) {
    CoordinatePair buttonA = {0, 0};
    CoordinatePair buttonB = {0, 0};
    CoordinatePair prize = {0, 0};

    for (size_t i = 0; i < inputGroup.size(); ++i) {
        std::stringstream lineStream(inputGroup[i]);
        std::string token;
        long long x = 0, y = 0;

        while (lineStream >> token) {
            if (token.find("X+") != std::string::npos || token.find("X=") != std::string::npos) {
                x = std::stoll(token.substr(2));
            } else if (token.find("Y+") != std::string::npos || token.find("Y=") != std::string::npos) {
                y = std::stoll(token.substr(2));
            }
        }

        if (i == 0) {
            buttonA = {x, y};
        } else if (i == 1) {
            buttonB = {x, y};
        } else if (i == 2) {
            prize = {x, y};
        }
    }

    return {buttonA, buttonB, prize};
}

CoordinatePair solveSystem(const CoordinatePair &A, const CoordinatePair &B, const CoordinatePair &total) {
    const long long buttonPressesBnum = total.y * A.x - A.y * total.x;
    const long long buttonPressesBden = A.x * B.y - A.y * B.x;

    if (buttonPressesBnum % buttonPressesBden == 0) {
        const auto buttonPressesB = buttonPressesBnum / buttonPressesBden;

        const auto buttonPressesAnum = total.x - buttonPressesB * B.x;

        if (buttonPressesAnum % A.x == 0) {
            return {buttonPressesAnum / A.x, buttonPressesB};
        }
    }

    return {0, 0};
}

int main() {
    std::stringstream input = readInputData(13);
    std::string line;
    std::vector<std::string> group;

    long long totalTokens = 0;
    long long prizesWon = 0;
    long long totalTokensAdjusted = 0;
    long long prizesWonAdjusted = 0;

    while (std::getline(input, line)) {
        if (line.empty()) continue;

        group.push_back(line);

        if (group.size() == 3) {
            auto [buttonA, buttonB, prize] = extractData(group);

            CoordinatePair tokens = solveSystem(buttonA, buttonB, prize);
            totalTokens += tokens.x*3;
            totalTokens += tokens.y;
            if (tokens.x > 0 || tokens.y > 0) {
                prizesWon++;
            }

            prize.x += 10000000000000;
            prize.y += 10000000000000;
            tokens = solveSystem(buttonA, buttonB, prize);
            totalTokensAdjusted += tokens.x*3;
            totalTokensAdjusted += tokens.y;
            if (tokens.x > 0 || tokens.y > 0) {
              prizesWonAdjusted++;
            }

            group.clear();
        }
    }

    std::cout << "Total prizes won: " << prizesWon << std::endl;
    std::cout << "Minimum tokens spent: " << totalTokens << std::endl;

    std::cout << "Total prizes won after adjustment: " << prizesWonAdjusted << std::endl;
    std::cout << "Minimum tokens spent after adjustment: " << totalTokensAdjusted << std::endl;

    return EXIT_SUCCESS;
}
