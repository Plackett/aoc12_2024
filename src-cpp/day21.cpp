#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <utility>
#include "inputData.h"  // Assuming inputData.h provides readInputData(int)

const std::vector<std::string> keypad = {"789", "456", "123", ".0A"};
const std::vector<std::string> dpad = {".^A", "<v>"};

std::vector<char> solveKeypad(const std::string& input) {
    std::vector<char> directions;
    std::pair<int, int> currentPos = {3, 2};  // Starting at 'A' on the keypad

    for (const char& c : input) {
        bool found = false;
        for (size_t row = 0; row < keypad.size(); ++row) {
            for (size_t col = 0; col < keypad[row].size(); ++col) {
                if (keypad[row][col] == c) {
                    while (currentPos.first != row || currentPos.second != col) {
                        if (currentPos.first < row) {
                            directions.push_back('v');
                            currentPos.first++;
                        } else if (currentPos.first > row) {
                            directions.push_back('^');
                            currentPos.first--;
                        } else if (currentPos.second < col) {
                            directions.push_back('>');
                            currentPos.second++;
                        } else if (currentPos.second > col) {
                            directions.push_back('<');
                            currentPos.second--;
                        }
                    }
                    directions.push_back('A'); // Marking arrival
                    found = true;
                    break;
                }
            }
            if (found) break;
        }
    }
    return directions;
}

std::vector<char> solveDPad(const std::vector<char>& inputDirections) {
    std::vector<char> directions;
    std::pair<int, int> currentPos = {0, 2};  // Starting at 'A' on the D-Pad

    for (const char& target : inputDirections) {
        if (target == 'A') {
            directions.push_back('A');
            continue;
        }

        std::pair<int, int> targetPos = currentPos;
        if (target == '^') {
            if (currentPos.first > 0 && dpad[currentPos.first - 1][currentPos.second] != '.') {
                targetPos.first--;
            }
        } else if (target == 'v') {
            if (currentPos.first < dpad.size() - 1 && dpad[currentPos.first + 1][currentPos.second] != '.') {
                targetPos.first++;
            }
        } else if (target == '<') {
            if (currentPos.second > 0 && dpad[currentPos.first][currentPos.second - 1] != '.') {
                targetPos.second--;
            }
        } else if (target == '>') {
            if (currentPos.second < dpad[currentPos.first].size() - 1 && dpad[currentPos.first][currentPos.second + 1] != '.') {
                targetPos.second++;
            }
        }

        while (currentPos != targetPos) {
            if (currentPos.first < targetPos.first) {
                directions.push_back('v');
                currentPos.first++;
            } else if (currentPos.first > targetPos.first) {
                directions.push_back('^');
                currentPos.first--;
            } else if (currentPos.second < targetPos.second) {
                directions.push_back('>');
                currentPos.second++;
            } else if (currentPos.second > targetPos.second) {
                directions.push_back('<');
                currentPos.second--;
            }
        }
        directions.push_back('A'); // Marking arrival
    }
    return directions;
}

std::vector<char> solveDPadOfDPad(const std::vector<char>& inputDirections) {
    std::vector<char> directions;
    std::pair<int, int> currentPos = {0, 2};  // Starting at 'A' on the D-Pad

    for (const char& target : inputDirections) {
        if (target == 'A') {
            directions.push_back('A');
            continue;
        }

        std::pair<int, int> targetPos = currentPos;
        if (target == '^') {
            if (currentPos.first > 0 && dpad[currentPos.first - 1][currentPos.second] != '.') {
                targetPos.first--;
            }
        } else if (target == 'v') {
            if (currentPos.first < dpad.size() - 1 && dpad[currentPos.first + 1][currentPos.second] != '.') {
                targetPos.first++;
            }
        } else if (target == '<') {
            if (currentPos.second > 0 && dpad[currentPos.first][currentPos.second - 1] != '.') {
                targetPos.second--;
            }
        } else if (target == '>') {
            if (currentPos.second < dpad[currentPos.first].size() - 1 && dpad[currentPos.first][currentPos.second + 1] != '.') {
                targetPos.second++;
            }
        }

        while (currentPos != targetPos) {
            if (currentPos.first < targetPos.first) {
                directions.push_back('v');
                currentPos.first++;
            } else if (currentPos.first > targetPos.first) {
                directions.push_back('^');
                currentPos.first--;
            } else if (currentPos.second < targetPos.second) {
                directions.push_back('>');
                currentPos.second++;
            } else if (currentPos.second > targetPos.second) {
                directions.push_back('<');
                currentPos.second--;
            }
        }
        directions.push_back('A'); // Marking arrival
    }
    return directions;
}

std::string removeNonDigits(const std::string& str) {
    std::string result;
    for (char c : str) {
        if (std::isdigit(c)) {
            result += c;
        }
    }
    return result;
}

int main() {
    std::stringstream file = readInputData(21);
    std::vector<std::string> codes;
    std::string line;
    while (std::getline(file, line)) {
        codes.push_back(line);
    }

    int total = 0;
    for (const auto& code : codes) {
        std::vector<char> keypadInput = solveKeypad(code);
        std::vector<char> dpadInput = solveDPad(keypadInput);
        std::vector<char> dpadDpadInput = solveDPadOfDPad(dpadInput);
        total += std::stoi(removeNonDigits(code)) * dpadDpadInput.size();
    }

    std::cout << "The complexity of all of the codes combined is: " << total << std::endl;

    return EXIT_SUCCESS;
}
