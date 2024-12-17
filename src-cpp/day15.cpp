#include <vector>
#include "inputData.h"
#include <algorithm>

struct WideBox {
	int x,y,w,h;
	bool operator== (const WideBox &other) const {
		return x == other.x && y == other.y && w == other.w && h == other.h;
	}
};

std::vector<std::vector<char>> widenMap(const std::vector<std::vector<char>> &map, std::vector<WideBox>& boxes) {
	std::vector<std::vector<char>> newMap{};
	for(int i = 0; i < map.size(); i++) {
		std::vector<char> newLine{};
		for(int j = 0; j < map[0].size(); j++) {
			if(map[i][j] == '.') {
				newLine.push_back('.');
				newLine.push_back('.');
			} else if(map[i][j] == 'O') {
				boxes.push_back(WideBox{static_cast<int>(newMap.size()), static_cast<int>(newLine.size()),1,2});
				newLine.push_back('[');
				newLine.push_back(']');
			} else if(map[i][j] == '#') {
				newLine.push_back('#');
				newLine.push_back('#');
			} else if(map[i][j] == '@') {
				newLine.push_back('@');
				newLine.push_back('.');
			}
		}
		newMap.push_back(newLine);
	}
	return newMap;
}

void moveBoxesWide(std::vector<std::vector<char>> &map, std::vector<WideBox>& boxes, std::pair<int, int> &pos, char direction) {
	int dx = 0, dy = 0;

	if (direction == '^') dx = -1;
	else if (direction == 'v') dx = 1;
	else if (direction == '<') dy = -1;
	else if (direction == '>') dy = 1;

	int newX = pos.first + dx;
	int newY = pos.second + dy;

	if (newX <= 0 || newX >= map.size() - 1 || newY <= 1 || newY >= map[0].size() - 2) return;

	if (map[newX][newY] == '.') {
		map[pos.first][pos.second] = '.';
		pos = {newX, newY};
		map[newX][newY] = '@';
	} else if (map[newX][newY] == '[' || map[newX][newY] == ']')
	{
		int boxX = newX;
		int boxY = newY;

		std::vector<int> boxChain;
		WideBox currentBox{};
		WideBox currentBoxLeft{};
		currentBox.w = 1;
		currentBox.h = 2;
		if (map[boxX][boxY] == '[') {
			currentBox.x = boxX;
			currentBox.y = boxY;
			currentBoxLeft.x = boxX;
			currentBoxLeft.y = boxY+1;
		} else {
			boxY--;
			currentBox.x = boxX;
			currentBox.y = boxY;
			currentBoxLeft.x = boxX;
			currentBoxLeft.y = boxY+1;
		}

		if(dy != 0) {
			while (std::find(boxes.begin(),boxes.end(),currentBox) != boxes.end()) {
				int index = std::find(boxes.begin(),boxes.end(),currentBox)-boxes.begin();
				boxChain.push_back(index);
				boxX += dx;
				boxY += dy;
				if (map[boxX][boxY] == '[') {
					boxY += dy;
					currentBox.x = boxX;
					currentBox.y = boxY-1;
				} else {
					currentBox.x = boxX;
					currentBox.y = boxY-1;
				}
			}

			if (boxX > 0 && boxX < map.size() - 1 && boxY > 1 && boxY < map[0].size() - 2 && map[boxX][boxY] == '.') {
				for (const int i : boxChain) {
					map[boxes.at(i).x + dx][boxes.at(i).y + dy] = '[';
					map[boxes.at(i).x + dx][boxes.at(i).y + dy + 1] = ']';
					boxes.at(i).x += dx;
					boxes.at(i).y += dy;
				}

				map[newX][newY] = '@';
				map[pos.first][pos.second] = '.';
				pos = {newX, newY};
			}
		}
		if(dx != 0) {
			// TODO: write vertical logic that works for boxes pushing other boxes
		}
	}
}

int calculateGPS(const std::vector<std::vector<char>> &map) {
	int GPS = 0;
	for(int i = 0; i < map.size(); i++) {
		for(int j = 0; j < map[0].size(); j++) {
			if(map[i][j] == 'O' || map[i][j] == '[') {
				GPS += i*100 + j;
			}
		}
	}
	return GPS;
}

void moveBoxes(std::vector<std::vector<char>> &map, std::pair<int, int> &pos, char direction) {
	int dx = 0, dy = 0;

	if (direction == '^') dx = -1;
	else if (direction == 'v') dx = 1;
	else if (direction == '<') dy = -1;
	else if (direction == '>') dy = 1;

	int newX = pos.first + dx;
	int newY = pos.second + dy;

	if (newX <= 0 || newX >= map.size() - 1 || newY <= 0 || newY >= map[0].size() - 1) return;

	if (map[newX][newY] == '.') {
		map[pos.first][pos.second] = '.';
		pos = {newX, newY};
		map[newX][newY] = '@';
	} else if (map[newX][newY] == 'O')
	{
		int boxX = newX;
		int boxY = newY;

		std::vector<std::pair<int, int>> boxChain;
		while (boxX > 0 && boxX < map.size() - 1 && boxY > 0 && boxY < map[0].size() - 1 && map[boxX][boxY] == 'O') {
			boxChain.emplace_back(boxX, boxY);
			boxX += dx;
			boxY += dy;
		}

		if (boxX > 0 && boxX < map.size() - 1 && boxY > 0 && boxY < map[0].size() - 1 && map[boxX][boxY] == '.') {
			for (int i = static_cast<int>(boxChain.size()) - 1; i >= 0; i--) {
				map[boxChain[i].first + dx][boxChain[i].second + dy] = 'O';
				map[boxChain[i].first][boxChain[i].second] = '.';
			}

			map[newX][newY] = '@';
			map[pos.first][pos.second] = '.';
			pos = {newX, newY};
		}
	}
}

int main()
{
	std::stringstream file = readInputData(15);
	std::string line;
	bool mapping = true;
	std::vector<std::vector<char>> map{};
	std::string directions{};
	std::pair<int,int> currentPos{};
	while (std::getline(file, line)) {
		if(line.empty())
			mapping = false;
		if(mapping) {
			if(line.find('@') != std::string::npos)
				currentPos = {map.size(),line.find('@')};
			map.emplace_back(line.begin(),line.end());
		} else {
			directions += line;
		}
	}

	std::vector<WideBox> boxes{};

	std::vector<std::vector<char>> wideMap = widenMap(map, boxes);
	std::pair widePos = {currentPos.first,currentPos.second*2};

	for(const auto direction : directions) {
		moveBoxes(map, currentPos, direction);
	}

	std::cout << "Sum of GPS Coordinates: " << calculateGPS(map) << std::endl;

	for(const auto direction : directions) {
		moveBoxesWide(wideMap, boxes, widePos, direction);
	}

	std::cout << "Sum of GPS Coordinates after widening: " << calculateGPS(wideMap) << std::endl;

	return EXIT_SUCCESS;
}
