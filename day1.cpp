#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

int main() {
    std::ifstream file("./input1.txt");
    if(!file.is_open())
        return EXIT_FAILURE;
    std::string line;
    std::vector<long long> leftList{};
    std::vector<long long> rightList{};
    while(std::getline(file, line)) {
        leftList.push_back(std::stoll(line.substr(0, line.find_first_of(' '))));
        rightList.push_back(std::stoll(line.substr(line.find_first_of(' '))));
    }
    std::sort(leftList.begin(), leftList.end());
    std::sort(rightList.begin(), rightList.end());
    long long distanceSum = 0;
    for(int i = 0; i < leftList.size(); i++) {
        distanceSum += std::abs(leftList[i] - rightList[i]);
    }
    std::cout << "Distance Sum: " << distanceSum << std::endl;
    distanceSum = 0;
    int occurrences = 0;
    for(long long & i : leftList) {
        occurrences = 0;
        for(const long long j : rightList) {
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
