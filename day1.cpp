#include <algorithm>
#include <iostream>
#include <vector>
#include "inputData.h"
#include <cstdint>

int main() {
    std::ifstream file = readInputData(1);
    std::string line;
    std::vector<int32_t> leftList{};
    std::vector<int32_t> rightList{};
    while(std::getline(file, line)) {
        leftList.push_back(std::stol(line.substr(0, line.find_first_of(' '))));
        rightList.push_back(std::stol(line.substr(line.find_first_of(' '))));
    }
    std::sort(leftList.begin(), leftList.end());
    std::sort(rightList.begin(), rightList.end());
    int32_t distanceSum = 0;
    for(int i = 0; i < leftList.size(); i++) {
        distanceSum += std::abs(leftList[i] - rightList[i]);
    }
    std::cout << "Distance Sum: " << distanceSum << std::endl;
    distanceSum = 0;
    int occurrences = 0;
    for(int32_t & i : leftList) {
        occurrences = 0;
        for(const int32_t j : rightList) {
            if(j == i) {
                occurrences++;
            }
        }
        i = i * occurrences;
        distanceSum += i;
    }
    std::cout << "Similarity Score: " << distanceSum << std::endl;
    file.close();
    return EXIT_SUCCESS;
}
