#include <algorithm>
#include <map>
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

#include <utility>

std::set<std::pair<int,int>> expandRegion(const std::set<std::pair<int, int>> &region) {
	std::set<std::pair<int,int>> result{};
	for(auto [fst, snd] : region) {
		for(int j = 0; j < 3; j++) {
			for(int k = 0; k < 3; k++) {
				result.insert({fst*3 + j, snd*3 + k});
			}
		}
	}
	return result;
}

int findSides(const std::set<std::pair<int, int>> &region, const std::pair<int, int> &start, int m, int n) {
	std::pair current = {start.first-1,start.second-1};
	int sides = 0;

	std::vector<std::pair<int, int>> direction = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
	int currentDirection = 0;

	auto isValid = [&](const std::pair<int, int> &cell) {
		return cell.first >= 0 && cell.first < m && cell.second >= 0 && cell.second < n && region.count(cell) > 0;
	};

	std::set<std::pair<std::pair<int, int>, int>> visited;
	int previousDirection = -1;

	do {

		std::pair next = {current.first + direction[currentDirection].first,
									current.second + direction[currentDirection].second};

		if (isValid({next.first-direction[(currentDirection+2)%4].first,next.second-direction[(currentDirection+2)%4].second})) {
			if (currentDirection != previousDirection) {
				sides++;
				previousDirection = currentDirection;
			}
			current = next;
			visited.insert({current, currentDirection});
			// logic error found, have to turn counterclockwise to hug the edge
			currentDirection = (currentDirection + 3) % 4;
		} else {
			currentDirection = (currentDirection + 1) % 4;
		}

	} while (current != start || currentDirection != 0);
	return sides;
}


// DFS algorimthm
aps floodFill(std::vector<std::vector<char>>& matrix, std::pair<int,int> start, char currentChar) {
	std::set region{start};

	const int m = matrix.size();
	const int n = matrix[0].size();
	int perimeter = 0;
   
	region = dfs(matrix,region,start.first,start.second,m,n,currentChar);
	bool sameSide = false;

	std::map<std::pair<int,int>, int> edges{};

	for(auto plant : region) {
		int numNeighbors = 0;
		if(region.find({plant.first-1,plant.second}) != region.end()) numNeighbors++;
		if(region.find({plant.first+1,plant.second}) != region.end()) numNeighbors++;
		if(region.find({plant.first,plant.second-1}) != region.end()) numNeighbors++;
		if(region.find({plant.first,plant.second+1}) != region.end()) numNeighbors++;
		if(numNeighbors < 4)
			edges.emplace(plant,numNeighbors);
		perimeter += 4 - numNeighbors;
	}

	const int uniqueEdges = findSides(expandRegion(region),start,m,n);

	return {static_cast<int>(region.size()),perimeter,uniqueEdges};
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