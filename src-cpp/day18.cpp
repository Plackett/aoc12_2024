#include <algorithm>
#include <iostream>
#include <vector>
#include <climits>
#include <list>
#include <set>
#include <sstream>

#include "inputData.h"

#define WIDTH 71
#define HEIGHT 71
#define PROCESS 1024

// Direction corresponds to dx, dy, easier to start facing EAST = 0
enum Direction { EAST, SOUTH, WEST, NORTH };

constexpr int dx[] = {0, 1, 0, -1};
constexpr int dy[] = {1, 0, -1, 0};

struct State {
    int x, y, price;
    Direction dir;
    std::list<std::pair<int, int>> path;
};

inline bool isValid(int x, int y, const std::set<std::pair<int, int>>& grid) {
    return x >= 0 && x < HEIGHT && y >= 0 && y < WIDTH && grid.find({x, y}) == grid.end();
}

std::pair<int, int> solveMaze(const std::set<std::pair<int, int>>& corrupted) {
    std::list<State> currentPositions;
    std::vector<std::vector<int>> visited(HEIGHT, std::vector<int>(WIDTH, INT_MAX));

    int bestCost = INT_MAX;
    std::list<State> bestPaths;

    State startState = {0, 0, 0, EAST, {{0, 0}}};
    currentPositions.push_back(startState);

    while (!currentPositions.empty()) {
        std::list<State> nextPositions;

        for (const auto& state : currentPositions) {
            if (visited[state.x][state.y] <= state.price) continue;
            visited[state.x][state.y] = state.price;

            if (state.x == HEIGHT - 1 && state.y == WIDTH - 1) {
                if (state.price < bestCost) {
                    bestCost = state.price;
                    bestPaths.clear();
                }
                if (state.price == bestCost) {
                    bestPaths.push_back(state);
                }
                continue;
            }

            for (int turn = -1; turn <= 1; ++turn) {
                int newDir = (state.dir + 4 + turn) % 4;
                int nx = state.x + dx[newDir];
                int ny = state.y + dy[newDir];

                if (isValid(nx, ny, corrupted)) {
                    auto newPath = state.path;
                    newPath.emplace_back(nx, ny);
                    nextPositions.push_back({nx, ny, state.price + 1, static_cast<Direction>(newDir), newPath});
                }
            }
        }

        currentPositions.swap(nextPositions);
    }

    std::vector<std::vector<char>> maze(HEIGHT, std::vector<char>(WIDTH, '.'));
    int pathTileCount = 0;

    for (const auto& state : bestPaths) {
        for (const auto& [x, y] : state.path) {
            if (maze[x][y] != 'O') ++pathTileCount;
            maze[x][y] = 'O';
        }
    }

    for (const auto& [x, y] : corrupted) {
        maze[x][y] = '#';
    }

    return {bestCost, pathTileCount};
}

int main() {
    std::stringstream file = readInputData(18);
    std::string line;

    std::set<std::pair<int, int>> corruptedBytes;
    std::vector<std::pair<int,int>> fullCorruption;

    while (std::getline(file, line)) {
        int x = std::stoi(line.substr(0, line.find(',')));
        int y = std::stoi(line.substr(line.find(',') + 1));
        if(corruptedBytes.size() < PROCESS)
            corruptedBytes.insert({y, x});
        fullCorruption.emplace_back(y,x);
    }

    auto [cost, pathLength] = solveMaze(corruptedBytes);
    if (cost != INT_MAX) {
        std::cout << "Number of steps to get to the exit: " << cost << '\n';
    } else {
        std::cout << "No path found from S to E." << '\n';
    }

    std::set<std::pair<int, int>> corruptedPartition = corruptedBytes;

    for(int i = PROCESS; i < 3000; i++)
        corruptedPartition.insert(fullCorruption[i]);

    for(int i = 3000; i < fullCorruption.size(); i++) {
        corruptedPartition.insert(fullCorruption[i]);
        if(solveMaze(corruptedPartition).first == INT_MAX) {
            std::cout << "First byte to close off exit: " << fullCorruption[i].second << "," << fullCorruption[i].first << std::endl;
            break;
        }
    }

    return EXIT_SUCCESS;
}