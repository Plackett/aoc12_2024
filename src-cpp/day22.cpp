#include <array>
#include <vector>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <unordered_map>

constexpr int CHANGE_COUNT = 4;
constexpr int SEQUENCE_LENGTH = 2000;
constexpr int PRICE_RANGE = 20;

long get_next_num(long cur_num) {
    cur_num = (((cur_num << 6) ^ cur_num) % (1 << 24));
    cur_num = (((cur_num >> 5) ^ cur_num) % (1 << 24));
    cur_num = (((cur_num << 11) ^ cur_num) % (1 << 24));
    return cur_num;
}

struct SequenceSum {
    long sum = 0;
    long last_seed_seen = -1;
};

struct ArrayHash {
    std::size_t operator()(const std::array<int, CHANGE_COUNT>& arr) const {
        std::size_t hash = 0;
        for (const int value : arr) {
            hash ^= std::hash<int>{}(value) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
        }
        return hash;
    }
};

int main() {
    std::vector<long> secretNumbers;
    std::string line;
    while (std::getline(std::cin, line)) {
        secretNumbers.push_back(std::stol(line));
    }

    long largest_sum = 0;

    std::unordered_map<std::array<int,2000>, std::unordered_map<int,int>, ArrayHash> sequence;

    for (int i = 0; i < secretNumbers.size(); i++) {
        long temp = secretNumbers[i];
        int last = temp % 10;
        std::array<int,4> currentSequence{0,0,0,0};
        for(int j = 0; j < 2000; j++) {
            temp = get_next_num(temp);
            currentSequence[0] = currentSequence[1];
            currentSequence[1] = currentSequence[2];
            currentSequence[2] = currentSequence[3];
            currentSequence[3] = temp % 10 - last;
            last = temp % 10;
            if(sequence.find(currentSequence) != sequence.end()) {}
            std::unordered_map<int,int> tempSequence{};
            tempSequence.insert(i,static_cast<int>(temp % 10));
        }
    }





    std::cout << largest_sum << std::endl;
    return 0;
}
