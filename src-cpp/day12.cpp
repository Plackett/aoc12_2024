#include <queue>
#include <set>
#include <vector>

#include "inputData.h"

struct aps {
	int area, perimeter, sides;
};

std::set<std::pair<int, int>> dfs(std::vector<std::vector<char>> &grid, std::set<std::pair<int,int>>& existing, int i, int j, int m, int n, char currentChar) {
	if(i >= 0 && i < m && j >= 0 && j < n && grid[i][j] == currentChar) {
		existing.insert({i,j});
		grid[i][j] = '.';
		dfs(grid, existing, i - 1, j, m, n, currentChar);
		dfs(grid, existing, i + 1, j, m, n, currentChar);
		dfs(grid, existing, i, j - 1, m, n, currentChar);
		dfs(grid, existing, i, j + 1, m, n, currentChar);
	}
	return existing;
}

// DFS algorimthm
aps floodFill(std::vector<std::vector<char>>& matrix, std::pair<int,int> start, char currentChar) {
	std::set region{start};

	const int m = matrix.size();
	const int n = matrix[0].size();
	int perimeter = 0;
   
	region = dfs(matrix,region,start.first,start.second,m,n,currentChar);
	bool sameSide = false;

	for(auto plant : region) {
		int numNeighbors = 0;
		if(region.find({plant.first-1,plant.second}) != region.end()) numNeighbors++;
		if(region.find({plant.first+1,plant.second}) != region.end()) numNeighbors++;
		if(region.find({plant.first,plant.second-1}) != region.end()) numNeighbors++;
		if(region.find({plant.first,plant.second+1}) != region.end()) numNeighbors++;
		perimeter += 4 - numNeighbors;
	}

	std::pair<int,int> current = start;

	int uniqueSides = 0;

	return {static_cast<int>(region.size()),perimeter,uniqueSides};
}

int main() {
	std::stringstream file = readInputData(12);

	std::vector<std::vector<char>> data{};

	std::string line;

	while(std::getline(file,line)) {
		std::vector temp(line.begin(), line.end());
		data.emplace_back(temp);
	}

	int totalPrice = 0;
	int totalPriceSides = 0;

	for(int i = 0; i < data.size(); ++i) {
		for(int j = 0; j < data[i].size(); ++j) {
			if(data[i][j] == '.') continue;
			auto [area, perimeter, sides] = floodFill(data, {i,j}, data[i][j]);
			totalPrice += area * perimeter;
			totalPriceSides += area * sides;
		};
	}

	std::cout << "Price of plants: " << totalPrice << std::endl;
	std::cout << "Price of plants with bulk discount: " << totalPriceSides << std::endl;

	return EXIT_SUCCESS;
}