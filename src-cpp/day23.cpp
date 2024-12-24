#include <iostream>
#include <set>
#include <vector>
#include <sstream>
#include <string>
#include <algorithm>
#include <numeric>

#include "inputData.h"

// Helper function to check if a group is fully connected
bool isFullyConnected(const std::set<std::string>& group, const std::set<std::pair<std::string, std::string>>& connections) {
    for (const auto& a : group) {
        for (const auto& b : group) {
            if (a != b && connections.count({a, b}) == 0) {
                return false;
            }
        }
    }
    return true;
}

// Find the largest clique in the network
std::set<std::string> findLargestClique(
    const std::set<std::string>& computers,
    const std::set<std::pair<std::string, std::string>>& connections) {
    std::set<std::string> largestClique;
    size_t n = computers.size();
    std::vector<std::string> computerList(computers.begin(), computers.end());

    // Debug: Output all computers
    std::cout << "Computers: ";
    for (const auto& comp : computers) {
        std::cout << comp << " ";
    }
    std::cout << std::endl;

    // Check all subsets of computers for the largest fully connected group
    for (size_t i = 0; i < (1 << n); ++i) {
        std::set<std::string> candidate;
        for (size_t j = 0; j < n; ++j) {
            if (i & (1 << j)) {
                candidate.insert(computerList[j]);
            }
        }
        if (candidate.size() > largestClique.size() && isFullyConnected(candidate, connections)) {
            largestClique = candidate;
        }
    }

    // Debug: Output largest clique
    std::cout << "Largest clique size: " << largestClique.size() << std::endl;
    std::cout << "Largest clique: ";
    for (const auto& comp : largestClique) {
        std::cout << comp << " ";
    }
    std::cout << std::endl;

    return largestClique;
}

int main() {
    std::stringstream file = readInputData(23);
    std::string line;
    std::set<std::pair<std::string, std::string>> connections;
    std::set<std::string> computers;

    // Parse input connections
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string fst, snd;
        if (std::getline(iss, fst, '-') && std::getline(iss, snd)) {
            connections.emplace(fst, snd);
            connections.emplace(snd, fst); // Add reverse connection for undirected graph
            computers.insert(fst);
            computers.insert(snd);
        }
    }

    // Debug: Output all connections
    std::cout << "Connections:" << std::endl;
    for (const auto& conn : connections) {
        std::cout << conn.first << "-" << conn.second << std::endl;
    }

    // Find the largest clique
    std::set<std::string> largestClique = findLargestClique(computers, connections);

    // Generate LAN party password
    std::vector<std::string> sortedClique(largestClique.begin(), largestClique.end());
    std::sort(sortedClique.begin(), sortedClique.end());
    std::string password = std::accumulate(
        sortedClique.begin(), sortedClique.end(),
        std::string(),
        [](const std::string& a, const std::string& b) {
            return a.empty() ? b : a + "," + b;
        });

    // Find all valid trios and count those with at least one computer starting with 't'
    int possible = 0;
    std::vector<std::vector<std::string>> validTrios;
    for (auto it1 = largestClique.begin(); it1 != largestClique.end(); ++it1) {
        for (auto it2 = std::next(it1); it2 != largestClique.end(); ++it2) {
            for (auto it3 = std::next(it2); it3 != largestClique.end(); ++it3) {
                std::vector<std::string> trio = {*it1, *it2, *it3};
                if (isFullyConnected({*it1, *it2, *it3}, connections)) {
                    validTrios.push_back(trio);
                    for (const auto& str : trio) {
                        if (str.at(0) == 't') {
                            possible++;
                            break;
                        }
                    }
                }
            }
        }
    }

    // Output results
    std::cout << "Largest clique password: " << password << std::endl;
    std::cout << "Number of valid trios: " << validTrios.size() << std::endl;
    std::cout << "Number of trios with at least one computer starting with 't': " << possible << std::endl;

    return EXIT_SUCCESS;
}
