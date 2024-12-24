#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <set>
#include <map>
#include "inputData.h"

struct State {
    int x, y, time;
    bool cheating;
};

bool is_valid(int x, int y, const std::vector<std::string>& map) {
    return x >= 0 && y >= 0 && x < map.size() && y < map[0].size();
}

int bfs(const std::vector<std::string>& map, std::pair<int, int> start, std::pair<int, int> end) {
    std::queue<State> q;
    std::set<std::pair<int, int>> visited;
    q.push({start.first, start.second, 0, false});
    visited.insert(start);

    std::vector<int> dx = {-1, 1, 0, 0}, dy = {0, 0, -1, 1};

    while (!q.empty()) {
        State curr = q.front();
        q.pop();

        if (curr.x == end.first && curr.y == end.second) {
            return curr.time;
        }

        for (int i = 0; i < 4; ++i) {
            int nx = curr.x + dx[i], ny = curr.y + dy[i];
            if (is_valid(nx, ny, map) && map[nx][ny] != '#' && !visited.count({nx, ny})) {
                visited.insert({nx, ny});
                q.push({nx, ny, curr.time + 1, false});
            }
        }
    }
    return -1; // No path found
}

int main() {
    std::stringstream file = readInputData(20);
    std::vector<std::string> map;
    std::string line;
    while (std::getline(file, line)) {
        map.push_back(line);
    }

    int rows = map.size(), cols = map[0].size();
    std::pair<int, int> start, end;

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (map[i][j] == 'S') start = {i, j};
            if (map[i][j] == 'E') end = {i, j};
        }
    }

    int normal_time = bfs(map, start, end);
    std::map<std::tuple<int, int, int, int>, int> cheats;

    std::vector<int> dx = {-1, 1, 0, 0}, dy = {0, 0, -1, 1};

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (map[i][j] == '#') {
                for (int d = 0; d < 4; ++d) {
                    for (int step = 1; step <= 2; ++step) {
                        int x1 = i - dx[d], y1 = j - dy[d];
                        int x2 = i + step * dx[d], y2 = j + step * dy[d];
                        if (is_valid(x1, y1, map) && is_valid(x2, y2, map) &&
                            map[x1][y1] != '#' && map[x2][y2] != '#') {
                            int time_to_cheat = bfs(map, start, {x1, y1});
                            int time_from_cheat = bfs(map, {x2, y2}, end);
                            if (time_to_cheat != -1 && time_from_cheat != -1) {
                                int total_time = time_to_cheat + step + time_from_cheat;
                                int time_saved = normal_time - total_time;
                                if (time_saved > 0) {
                                    cheats[{x1, y1, x2, y2}] = std::max(cheats[{x1, y1, x2, y2}], time_saved);
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    int count = 0;
    for (const auto& [cheat, time_saved] : cheats) {
        if (time_saved >= 100) {
            count++;
        }
    }

    std::cout << "Number of cheats saving at least 100 picoseconds: " << count << std::endl;

    return 0;
}
