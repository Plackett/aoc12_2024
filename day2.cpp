#include <iostream>
#include <vector>

#include "inputData.h"

int main() {
	std::ifstream file = readInputData(2);
	std::vector<std::vector<int>> levelData{};
	std::string line;
	while(std::getline(file,line)) {
		std::vector<int> levels{};
		int head = 0;
		for(int i = 0; i < line.size(); i++) {
			if(isspace(line[i]) || i == line.size() - 1) {
				levels.push_back(std::stoi(line.substr(head,i)));
				head = i+1;
			}
		}
		levelData.push_back(levels);
	}
	bool increasing = true;
	bool safe = true;
	int safeCount = 0;
	for(auto & i : levelData) {
		safe = true;
		increasing = i[0] < i[1];
		for(int j = 1; j < i.size(); j++) {
			if(i[j-1] > i[j] && increasing) {
				safe = false;
				break;
			}
			if(i[j-1] < i[j] && !increasing) {
				safe = false;
				break;
			}
			if(std::abs(i[j-1] - i[j]) > 3 || i[j-1] - i[j] == 0) {
				safe = false;
				break;
			}
		}
		if(safe)
			safeCount++;
	}
	std::cout << safeCount << " reports are safe." << std::endl;
	safeCount = 0;
	for(const auto & i : levelData) {
		for(int j = 0; j < i.size(); j++) {
			std::vector<int> tmp = i;
			tmp.erase(tmp.begin()+j);
			safe = true;
			increasing = tmp[0] < tmp[1];
			for(int k = 1; k < tmp.size(); k++) {
				if(tmp[k-1] > tmp[k] && increasing) {
					safe = false;
					break;
				}
				if(tmp[k-1] < tmp[k] && !increasing) {
					safe = false;
					break;
				}
				if(std::abs(tmp[k-1] - tmp[k]) > 3 || tmp[k-1] - tmp[k] == 0) {
					safe = false;
					break;
				}
			}
			if(safe) {
				safeCount++;
				break;
			}
		}

	}
	std::cout << safeCount << " reports are safe with one bad level." << std::endl;
	return EXIT_SUCCESS;
}