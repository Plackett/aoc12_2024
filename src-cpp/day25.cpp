#include <vector>

#include "inputData.h"

int main() {
	std::stringstream file = readInputData(25);
	std::string line;
	std::vector<std::vector<int>> keys{};
	std::vector<std::vector<int>> locks{};
	std::vector<int> current{};
	bool keyLock = false;
	while (std::getline(file, line)) {
		if(line.empty()) {
			if(keyLock) {
				locks.push_back(current);
				current.clear();
			} else {
				keys.push_back(current);
				current.clear();
			}
			continue;
		}
		if(current.empty()) {
			if(line.at(0) == '#')
				keyLock = true;
			else
				keyLock = false;
			current = std::vector(line.size(),0);
			continue;
		}
		for(int i = 0; i < line.size(); i++) {
			if(line.at(i) == '#') {
				current.at(i) = current.at(i) + 1;
			}
		}
	}
	if(keyLock) {
		locks.push_back(current);
		current.clear();
	} else {
		keys.push_back(current);
		current.clear();
	}

	int possible = 0;
	for(auto& key : keys) {
		for(auto& lock : locks) {
			bool overlap = false;
			for(int i = 0; i < lock.size(); i++) {
				if(lock.at(i) + key.at(i) - 1 > 5)
					overlap = true;
			}
			if(!overlap)
				possible++;
		}
	}
	std::cout << "The number of possible lock/key combinations is: " << possible << std::endl;
	return EXIT_SUCCESS;
}