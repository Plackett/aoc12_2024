#include <algorithm>
#include <iostream>
#include <vector>
#include <climits>
#include <list>

#include "inputData.h"

// yeah Direction corresponds to dx, dy, easier to start facing EAST = 0
enum Direction { EAST, SOUTH, WEST, NORTH };

constexpr int dx[] = {0, 1, 0, -1};
constexpr int dy[] = {1, 0, -1, 0};

struct State {
    int x, y, price;
    Direction dir;
    std::list<std::pair<int, int>> path;
};

bool isValid(const int x, const int y, const int rows, const int cols, const std::vector<std::vector<char>>& grid) {
    return x >= 0 && x < rows && y >= 0 && y < cols && grid[x][y] != '#';
}


// I created this logic from ivop's solution: https://github.com/ivop/aoc2024/blob/ce108e58a2caeaf7d73ae1fab2c32883c5519e13/day16/both.cpp
std::pair<int, int> solveMaze(std::vector<std::vector<char>>& maze, const std::pair<int, int>& start, const std::pair<int, int>& end) {
    std::list<State> newPosition;
    std::list<State> positions;
    std::list<State> goodPaths;

    const int m = static_cast<int>(maze.size());
    const int n = static_cast<int>(maze[0].size());

    std::vector visited(m, std::vector(n, INT_MAX));

    int best = INT_MAX;

    State startState{start.first, start.second, 0, EAST, {}};
    startState.path.emplace_back(start.first, start.second);
    positions.push_back(startState);

    while (!positions.empty()) {
        for (const auto& p : positions) {
            // Avoid revisiting with worse cost
            if (visited[p.x][p.y] < p.price - 1000) continue;
            visited[p.x][p.y] = p.price;

            // Check if the end is reached
            if (p.x == end.first && p.y == end.second) {
                if (p.price < best) best = p.price;
                goodPaths.push_back(p);
                continue;
            }

            // Straight move
            int nd = p.dir;
            int nx = p.x + dx[nd];
            int ny = p.y + dy[nd];
            if (isValid(nx, ny, m, n, maze)) {
                auto newPath = p.path;
                newPath.emplace_back(nx, ny);
                newPosition.push_back({nx, ny, p.price + 1, static_cast<Direction>(nd), newPath});
            }

            // Turn left
            nd = (p.dir + 3) % 4;
            nx = p.x + dx[nd];
            ny = p.y + dy[nd];
            if (isValid(nx, ny, m, n, maze)) {
                auto newPath = p.path;
                newPath.emplace_back(nx, ny);
                newPosition.push_back({nx, ny, p.price + 1001, static_cast<Direction>(nd), newPath});
            }

            // Turn right
            nd = (p.dir + 1) % 4;
            nx = p.x + dx[nd];
            ny = p.y + dy[nd];
            if (isValid(nx, ny, m, n, maze)) {
                auto newPath = p.path;
                newPath.emplace_back(nx, ny);
                newPosition.push_back({nx, ny, p.price + 1001, static_cast<Direction>(nd), newPath});
            }
        }
        positions.clear();
        positions.swap(newPosition);
    }

    // Count tiles for the best paths
    int seats = 0;
    for (const auto&[x, y, price, dir, path] : goodPaths) {
        if (price != best) continue;
        for (const auto& [x, y] : path) {
            if (maze[x][y] != 'O') seats++;
            maze[x][y] = 'O';
        }
    }

    // Print maze with the best path
    for (const auto& row : maze) {
        for (const char c : row) {
            std::cout << c;
        }
        std::cout << "\n";
    }
    std::cout << std::endl;

    return {best, seats};
}

int main() {
    std::stringstream file = readInputData(16);
    std::string line;

    std::vector<std::vector<char>> maze;
    std::pair<int,int> start{}, end{};

    while (std::getline(file, line)) {
        maze.emplace_back(line.begin(), line.end());

        if (line.find('S') != std::string::npos) {
            start.first = static_cast<int>(maze.size()) - 1;
            start.second = static_cast<int>(line.find('S'));
        }

        if (line.find('E') != std::string::npos) {
            end.first = static_cast<int>(maze.size()) - 1;
            end.second = static_cast<int>(line.find('E'));
        }
    }

    if (const auto [cost, pathLength] = solveMaze(maze, start, end); cost != INT_MAX) {
        std::cout << "Lowest possible score: " << cost << std::endl;
        std::cout << "Number of tiles in all the best paths: " << pathLength << std::endl;
    } else {
        std::cout << "No path found from S to E." << std::endl;
    }

    return EXIT_SUCCESS;
}