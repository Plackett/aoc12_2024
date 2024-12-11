#include <vector>
#include <string>
#include "inputData.h"
#include <thread>
#include <mutex>
#include <cmath>
#include <unordered_map>

void countStones(long long& sum, std::unordered_map<long long, long long>& stones) {
	for (const auto& [stone, count] : stones) {
		sum += count;
	}
}

// counter optimizations really do be paying off
std::unordered_map<long long, long long> blink(const std::unordered_map<long long, long long>& stones) {
	std::unordered_map<long long, long long> newStones;

	for (const auto& [stone, count] : stones) {
		if (stone == 0) {
			newStones[1] += count;
		} else {
			int numDigits = std::log10(stone) + 1;
			if (numDigits % 2 == 0) {
				long long divisor = std::pow(10, numDigits / 2);
				long long left = stone / divisor;
				long long right = stone % divisor;
				newStones[left] += count;
				newStones[right] += count;
			} else {
				newStones[stone * 2024] += count;
			}
		}
	}

	return newStones;
}

int main() {
	std::stringstream file = readInputData(11);
	std::string line;
	std::unordered_map<long long, long long> stones;

	while (std::getline(file, line)) {
		std::istringstream lineStream(line);
		long long number;
		while (lineStream >> number) {
			stones[number]++;
		}
	}

	for (int i = 0; i < 25; i++) {
		stones = blink(stones);
	}

	long long totalStones = 0;
	countStones(totalStones, stones);

	std::cout << "Stones after blinking 25 times: " << totalStones << std::endl;

	for (int i = 0; i < 50; i++) {
		stones = blink(stones);
	}

	totalStones = 0;
	countStones(totalStones, stones);

	std::cout << "Stones after blinking 75 times: " << totalStones << std::endl;

	return EXIT_SUCCESS;
}