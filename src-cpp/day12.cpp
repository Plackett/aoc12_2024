#include <queue>
#include <vector>

#include "inputData.h"

struct aps {
	int area, perimeter, sides;
};

// BFS algorimthm
aps floodFill(std::vector<std::vector<char>>& matrix, int x,
							  int y, char currentChar) {
                                 
	std::queue<std::pair<int, int>> q;

	int m = matrix.size();
	int n = matrix[0].size();
	int perimeter = 0;
   
	char prevChar = matrix[x][y];
	if (prevChar == currentChar)
		return {1,4,4};

	q.emplace(x, y);
	matrix[x][y] = currentChar;
	
	while (!q.empty()) {

		x = q.front().first;
		y = q.front().second;
		q.pop();

		if (x + 1 < m && matrix[x + 1][y] == prevChar) {
			matrix[x + 1][y] = currentChar;
			q.emplace(x + 1, y);
		}
		if (x - 1 >= 0 && matrix[x - 1][y] == prevChar) {
			matrix[x - 1][y] = currentChar;
			q.emplace(x - 1, y);
		}
		if (y + 1 < n && matrix[x][y + 1] == prevChar) {
			matrix[x][y + 1] = currentChar;
			q.emplace(x, y + 1);
		}
		if (y - 1 >= 0 && matrix[x][y - 1] == prevChar) {
			matrix[x][y - 1] = currentChar;
			q.emplace(x, y - 1);
		}
	}

	int uniqueSides = 0;

	return {static_cast<int>(q.size()),perimeter,uniqueSides};
}

int main() {
	std::stringstream file = readInputData(12);

	std::vector<std::vector<char>> data{};

	std::string line;

	while(std::getline(file,line)) {
		std::vector temp(line.begin(), line.end());
		data.emplace_back(temp);
	}

	return EXIT_SUCCESS;
}