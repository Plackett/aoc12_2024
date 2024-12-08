#include <iostream>
#include <vector>
#include <algorithm>

#include "inputData.h"

// sorting helper function
void fixPageOrder(std::vector<int> &page, const std::vector<std::pair<int, int>> & comparisons) {
	auto comparator = [&comparisons](const int a, const int b) {
		for (const auto &[fst, snd] : comparisons) {
			if (a == fst && b == snd) return true;
			if (a == snd && b == fst) return false;
		}
		return false;
	};

	// Sort the update using the comparator
	std::sort(page.begin(), page.end(), comparator);
}

int main() {
	std::stringstream file = readInputData(5);
	std::vector<std::pair<int,int>> comparisons{};
	std::vector<std::vector<int>> pages{};
	std::string line;
	while(std::getline(file,line)) {
		// first section
		if(line.find('|') != std::string::npos) {
			const int location = line.find('|');
			comparisons.emplace_back(
				std::stoi(line.substr(0, location)),
				std::stoi(line.substr(location + 1))
			);
		} else {
			if(line.empty())
				continue;
			std::vector<int> update;
			std::stringstream ss(line);
			std::string page;
			while (std::getline(ss, page, ',')) {
				update.push_back(std::stoi(page));
			}
			pages.push_back(update);
		}
	}
	int sum = 0;
	int incorrectSum = 0;
	std::vector<int> correctPages{};
	// I don't like enhanced for loops but it was convienent here
	for (auto &page : pages) {
		bool correct = true;

		// Check all ordering rules for this update
		for (const auto &[fst, snd] : comparisons) {
			auto fstPos = std::find(page.begin(), page.end(), fst);
			auto sndPos = std::find(page.begin(), page.end(), snd);

			if (fstPos != page.end() && sndPos != page.end() && fstPos > sndPos) {
				correct = false;
				break;
			}
		}

		if (correct) {
			sum += page[page.size() / 2];
		} else {
			fixPageOrder(page, comparisons);
			incorrectSum += page[page.size() / 2];
		}
	}

	std::cout << "Middle numbers of correct lines = " << sum << std::endl;
	std::cout << "Middle numbers of incorrect lines = " << incorrectSum << std::endl;
	return EXIT_SUCCESS;
}
