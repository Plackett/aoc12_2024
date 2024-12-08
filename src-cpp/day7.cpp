#include <map>
#include <vector>
#include <cmath>

#include "inputData.h"

bool checkTarget(long long target, const std::vector<long long>& data, const std::vector<int>& operators) {
    long long total = data[0];
    for (long long i = 1; i < data.size(); i++) {
        if (operators[i - 1] == 0)
            total += data[i];
        else if( operators[i - 1] == 1)
            total *= data[i];
        else {
            std::string strTotal = std::to_string(total);
            strTotal += std::to_string(data[i]);
            total = std::stoll(strTotal);
        }
    }
    return total == target;
}

bool checkTarget(int target, const std::vector<long long>& data, const std::vector<bool>& operators) {
    int total = data[0];
    for (int i = 1; i < data.size(); i++) {
        if (operators[i - 1])
            total += data[i];
        else
            total *= data[i];
    }
    return total == target;
}

bool findCombination(const long long target, const std::vector<long long>& data) {
    int numOperators = data.size() - 1;
    int numCombinations = std::pow(2, numOperators);  // 2^numOperators

    for (int mask = 0; mask < numCombinations; mask++) {
        std::vector<bool> operators(numOperators);
        for (int i = 0; i < numOperators; i++) {
            operators[i] = (mask & (1 << i)) != 0;  // Extract bit i as operator
        }
        if (checkTarget(target, data, operators)) {
            return true;
        }
    }
    return false;
}

bool findCombinationWithConcat(const long long target, const std::vector<long long>& data) {
    const int numOperators = data.size() - 1;
    const int numCombinations = std::pow(3, numOperators);

    for (int mask = 0; mask < numCombinations; mask++) {
        std::vector<int> operators(numOperators);
        int tmpMask = mask;

        for (int i = 0; i < numOperators; i++) {
            operators[i] = tmpMask % 3;
            tmpMask /= 3;
        }
        if (checkTarget(target, data, operators)) {
            return true;
        }
    }
    return false;
}


int main() {

    std::stringstream file = readInputData(7);
    std::string line;
    std::map<long long, std::vector<long long>> data;

    while (std::getline(file, line)) {
        if (size_t colonPos = line.find(':'); colonPos != std::string::npos) {
            long long key = std::stoll(line.substr(0, colonPos));
            std::vector<long long> numbers;
            std::istringstream iss(line.substr(colonPos + 1));
            std::string num;
            while (iss >> num) {
                numbers.push_back(std::stoll(num));
            }
            data[key] = numbers;
        }
    }

    long long total = 0;
    long long totalConCat = 0;

    for (const auto&[result, datapoints] : data) {
        long long target = result;
        const auto& numbers = datapoints;

        if (numbers.empty()) continue;

        if (std::vector<bool> operators(numbers.size() - 1); findCombination(target, numbers)) {
            total += target;
        }
    }

    for (const auto&[result, datapoints] : data) {
        long long target = result;
        const auto& numbers = datapoints;

        if (numbers.empty()) continue;

        if (std::vector<int> operators(numbers.size() - 1); findCombinationWithConcat(target, numbers)) {
            totalConCat += target;
        }
    }

    std::cout << "Sum of possible equations: " << total << std::endl;
    std::cout << "Sum of possible equations with ||: " << totalConCat << std::endl;

    return EXIT_SUCCESS;
}
