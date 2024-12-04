#include <iostream>
#include <vector>

#include "inputData.h"

int main() {
	std::stringstream file = readInputData(4);
	std::string line;
	std::vector<std::string> map;
	int count = 0;
	int masCount = 0;
	while(std::getline(file,line)) {
	    map.push_back(line);
    }
	for (int i = 0; i < map.size(); i++) {
		for (int j = 0; j < map[i].size(); j++) {
			// --- Horizontal ---
			// Forward
			if (j + 3 < map[i].size() &&
				map[i][j] == 'X' && map[i][j+1] == 'M' &&
				map[i][j+2] == 'A' && map[i][j+3] == 'S') count++;

			// Backward
			if (j - 3 >= 0 &&
				map[i][j] == 'X' && map[i][j-1] == 'M' &&
				map[i][j-2] == 'A' && map[i][j-3] == 'S') count++;

			// --- Vertical ---
			// Forward
			if (i + 3 < map.size() &&
				map[i][j] == 'X' && map[i+1][j] == 'M' &&
				map[i+2][j] == 'A' && map[i+3][j] == 'S') count++;

			// Backward
			if (i - 3 >= 0 &&
				map[i][j] == 'X' && map[i-1][j] == 'M' &&
				map[i-2][j] == 'A' && map[i-3][j] == 'S') count++;

			// --- Diagonal Top-left to Bottom-right ---
			// Forward
			if (i + 3 < map.size() && j + 3 < map[i].size() &&
				map[i][j] == 'X' && map[i+1][j+1] == 'M' &&
				map[i+2][j+2] == 'A' && map[i+3][j+3] == 'S') count++;

			// Backward
			if (i - 3 >= 0 && j - 3 >= 0 &&
				map[i][j] == 'X' && map[i-1][j-1] == 'M' &&
				map[i-2][j-2] == 'A' && map[i-3][j-3] == 'S') count++;

			// --- Diagonal Bottom-left to Top-right ---
			// Forward
			if (i - 3 >= 0 && j + 3 < map[i].size() &&
				map[i][j] == 'X' && map[i-1][j+1] == 'M' &&
				map[i-2][j+2] == 'A' && map[i-3][j+3] == 'S') count++;

			// Backward
			if (i + 3 < map.size() && j - 3 >= 0 &&
				map[i][j] == 'X' && map[i+1][j-1] == 'M' &&
				map[i+2][j-2] == 'A' && map[i+3][j-3] == 'S') count++;

			// --- Diagonal Top-left to Bottom-right FOR x-mas ---
			if(i + 2 < map.size() && j + 2 < map.size() &&
				( (map[i][j] == 'M' && map[i+1][j+1] == 'A' && map[i+2][j+2] == 'S' && map[i+2][j] == 'M' && map[i+1][j+1] == 'A' && map[i][j+2] == 'S') ||
				(map[i][j] == 'S' && map[i+1][j+1] == 'A' && map[i+2][j+2] == 'M' && map[i+2][j] == 'S' && map[i+1][j+1] == 'A' && map[i][j+2] == 'M') ||
				(map[i][j] == 'M' && map[i+1][j+1] == 'A' && map[i+2][j+2] == 'S' && map[i+2][j] == 'S' && map[i+1][j+1] == 'A' && map[i][j+2] == 'M') ||
				(map[i][j] == 'S' && map[i+1][j+1] == 'A' && map[i+2][j+2] == 'M' && map[i+2][j] == 'M' && map[i+1][j+1] == 'A' && map[i][j+2] == 'S')
				)) masCount++;
		}
	}


	std::cout << "Number of times XMAS appears: " << count << std::endl;
	std::cout << "Number of times X-MAS appears: " << masCount << std::endl;
	return EXIT_SUCCESS;
}