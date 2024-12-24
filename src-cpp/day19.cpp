#include <set>
#include <vector>
#include <sstream>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>

#include "inputData.h"
#include <regex>

int canFormDesign(const std::string& design, const std::set<std::string>& available) {
  // this is literally the same code as day 16 except with *regex* instead of maze-solving
  std::unordered_map<std::string, int> memo;
  std::queue<std::string> toProcess;

  toProcess.push(design);
  memo[design] = 0;

  while (!toProcess.empty()) {
    std::string current = toProcess.front();
    toProcess.pop();

    if (memo[current] > 0) continue;

    int ways = 0;

    for (const auto& pattern : available) {
      if (current.rfind(pattern, 0) == 0) {
        std::string remaining = current.substr(pattern.size());

        if (remaining.empty()) {
          ways += 1;
        } else {
          if (memo.find(remaining) == memo.end()) {
            toProcess.push(remaining);
          }
          ways += memo[remaining];
        }
      }
    }

    memo[current] = ways;
  }

  return memo[design];
}

int main() {
  std::stringstream file = readInputData(19);
  std::set<std::string> candidates{};
  std::set<std::string> available{};
  std::string line;

  while (std::getline(file, line)) {
    if (line.find(',') != std::string::npos) {
      std::stringstream ss(line);
      std::string substring;
      while (std::getline(ss, substring, ',')) {
        if(substring.size() > 1)
          available.insert(substring.substr(1));
        else
          available.insert(substring);
      }
    } else if (!line.empty()) {
      candidates.insert(line);
    }
  }

  int possibleCount = 0;
  long long totalWays = 0;
  for (const auto& design : candidates) {
    int ways = canFormDesign(design, available);
    if(ways > 0)
      possibleCount++;
    totalWays += ways;
  }

  std::cout << possibleCount << " towels are possible." << std::endl;
  std::cout << totalWays << " number of ways to create every towel are possible." << std::endl;
  return EXIT_SUCCESS;
}