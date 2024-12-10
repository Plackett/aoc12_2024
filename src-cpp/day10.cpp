#include <vector>
#include <algorithm>

#include "inputData.h"

int findPath(std::vector<std::vector<int>> heightMap, std::pair<int,int> startPoint, std::vector<std::pair<int,int>> &visitedNines) {
	int rating = 0;
	std::pair<int,int> currentPoint = startPoint;
	int currentElevation = heightMap[currentPoint.first][currentPoint.second];
	while(currentElevation != 9) {
		currentElevation++;
		std::pair<int,int> futurePoint = currentPoint;
		std::vector<std::pair<int,int>> nextPoints = {{-1,0},{1,0},{0,-1},{0,1}};
		bool split = false;
		for(auto [dy, dx] : nextPoints) {
			int newY = currentPoint.first + dy;
			int newX = currentPoint.second + dx;
			if(newY >= 0 && newY < heightMap[newY].size() && newX >= 0 && newX < heightMap[newY].size()) {
				if(heightMap[newY][newX] == currentElevation) {
					if(split)
						rating += findPath(heightMap, {newY,newX}, visitedNines);
					else {
						split = true;
						futurePoint = {newY,newX};
					}
				}
			}
		}
		if(!split)
			return rating;
		currentPoint = futurePoint;
	}
	if(std::find(visitedNines.begin(),visitedNines.end(),currentPoint) == visitedNines.end()) {
		visitedNines.push_back(currentPoint);
	}
	return 1 + rating;
}

int main() {
	std::stringstream file = readInputData(10);
	std::string line;
	std::vector<std::vector<int>> heightMap{};
	std::vector<std::pair<int,int>> startPoints{};

	while(std::getline(file,line)) {
		std::vector<int> row{};
		for(char c : line) {
			row.push_back(c - '0');
			if(c == '0')
				startPoints.emplace_back(heightMap.size(),row.size()-1);
		}
		heightMap.push_back(row);
	}

	int numPaths = 0;
	int numRatings = 0;
	for(auto& point : startPoints) {
		std::vector<std::pair<int,int>> visitedNines{};
		numRatings += findPath(heightMap, point, visitedNines);
		numPaths += visitedNines.size();
	}

	std::cout << "Number of successful paths: " << numPaths << std::endl;
	std::cout << "Ratings of successful paths: " << numRatings << std::endl;
	return EXIT_SUCCESS;
}