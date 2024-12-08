#include "inputData.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <unordered_set>
#include <chrono>

struct vec2 {
	int x,y;
	bool operator==(const vec2 &other) const
	{
		return x == other.x && y == other.y;
	}
	bool operator<(const vec2 &other) const {
		return x < other.x || (x == other.x && y < other.y);
	}
};

// Hash function for vec2
struct vec2_hash {
	size_t operator()(const vec2 &v) const {
		return std::hash<int>()(v.x) ^ (std::hash<int>()(v.y) << 1);
	}
};

// Struct for state (position + direction)
struct posDir {
	vec2 pos, dir;

	bool operator==(const posDir &other) const {
		return pos == other.pos && dir == other.dir;
	}
};

// Hash function for state
struct posDir_hash {
	size_t operator()(const posDir &s) const {
		return vec2_hash()(s.pos) ^ (vec2_hash()(s.dir) << 1);
	}
};

int main() {
	auto t1 = std::chrono::high_resolution_clock::now();
	std::stringstream file = readInputData(6);
	std::string line;
	std::unordered_set<vec2,vec2_hash> obstacles{};
	vec2 guardPos;
	vec2 guardDir = vec2{0,-1};
	int horizontalSize = 0;
	int currLine = 0;
	while(std::getline(file,line)) {
		for(int i = 0; i < line.size(); i++) {
			if(line[i] == '#')
				obstacles.insert({i,currLine});
			if(line[i] == '^')
				guardPos = vec2{i,currLine};
		}
		horizontalSize = line.size();
		currLine++;
	}
	std::vector<vec2> uniquePos{};
	int uniqueSpaces = 0;
	vec2 guardPosOrig = guardPos;
	while(true) {
		if(std::find(obstacles.begin(),obstacles.end(),vec2{guardPos.x+guardDir.x,guardPos.y+guardDir.y}) != obstacles.end()) {
			// rotate
			if(guardDir.x == 0 && guardDir.y == 1) {
				guardDir.x = -1;
				guardDir.y = 0;
			} else if(guardDir.x == 1 && guardDir.y == 0) {
				guardDir.x = 0;
				guardDir.y = 1;
			} else if(guardDir.x == 0 && guardDir.y == -1) {
				guardDir.x = 1;
				guardDir.y = 0;
			} else if(guardDir.x == -1 && guardDir.y == 0) {
				guardDir.x = 0;
				guardDir.y = -1;
			}
			if(std::find(uniquePos.begin(), uniquePos.end(), guardPos) == uniquePos.end()) {
				uniquePos.push_back(guardPos);
				uniqueSpaces++;
			}
		} else {
			if(std::find(uniquePos.begin(), uniquePos.end(), guardPos) == uniquePos.end()) {
				uniquePos.push_back(guardPos);
				uniqueSpaces++;
			}
			guardPos.x += guardDir.x;
			guardPos.y += guardDir.y;
			if(guardPos.x < 0 || guardPos.y < 0 || guardPos.y >= currLine || guardPos.x >= horizontalSize)
				break;

		}
	}
	int infiniteLoops = 0;
	std::unordered_set<posDir, posDir_hash> traveledPosDir;
	for(int i = 1; i < uniquePos.size(); i++) {
		guardPos = guardPosOrig;
		guardDir = {0, -1};
		traveledPosDir = {};
		while(true) {
			vec2 testpos = {guardPos.x + guardDir.x, guardPos.y + guardDir.y};
			if(obstacles.find(testpos) != obstacles.end() || testpos == uniquePos[i]) {
				// rotate
				if(guardDir.x == 0 && guardDir.y == 1) {
					guardDir.x = -1;
					guardDir.y = 0;
				} else if(guardDir.x == 1 && guardDir.y == 0) {
					guardDir.x = 0;
					guardDir.y = 1;
				} else if(guardDir.x == 0 && guardDir.y == -1) {
					guardDir.x = 1;
					guardDir.y = 0;
				} else if(guardDir.x == -1 && guardDir.y == 0) {
					guardDir.x = 0;
					guardDir.y = -1;
				}
				if(traveledPosDir.find({guardPos,guardDir}) != traveledPosDir.end()) {
					infiniteLoops++;
					break;
				}
			} else {
				guardPos = testpos;
				if(testpos.x < 0 || testpos.y < 0 || testpos.y >= currLine || testpos.x >= horizontalSize)
					break;

			}
			if(traveledPosDir.find({guardPos,guardDir}) == traveledPosDir.end()) {
				traveledPosDir.insert({guardPos,guardDir});
			}
		}
	}
	auto t2 = std::chrono::high_resolution_clock::now();
	auto ms_int = duration_cast<std::chrono::milliseconds>(t2 - t1);
	std::cout << "elapsed time: " << ms_int.count() / 1000.00 << " s" << std::endl;
	std::cout << "Distinct spaces traveled: " << uniqueSpaces << std::endl;
	std::cout << "Infinite Loops: " << infiniteLoops << std::endl;
	return EXIT_SUCCESS;
}