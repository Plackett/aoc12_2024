#include <algorithm>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <map>

#include "inputData.h"

// this helper function ain't mine
void printInt128(__int128 num) {
    if (num == 0) {
        std::cout << "0";
        return;
    }

    std::string result = "";
    bool negative = num < 0;

    if (negative) {
        num = -num;
    }

    while (num > 0) {
        result = static_cast<char>('0' + num % 10) + result;
        num /= 10;
    }

    if (negative) {
        std::cout << "-";
    }

    std::cout << result;
}

std::map<int, int> findFreeSpaceSpans(const std::vector<int>& diskMap) {
    std::map<int, int> freeSpaceSpans;
    int start = -1;

    for (int i = 0; i < diskMap.size(); ++i) {
        if (diskMap[i] == -1) {
            if (start == -1) {
                start = i;
            }
        } else {
            if (start != -1) {
                freeSpaceSpans[start] = i - start;
                start = -1;
            }
        }
    }

    if (start != -1) {
        freeSpaceSpans[start] = diskMap.size() - start;
    }

    return freeSpaceSpans;
}

int main() {
    std::stringstream file = readInputData(9);
    std::vector<int> blocks;
    std::string line;

    while (std::getline(file, line)) {
        for (const char i : line) {
            blocks.push_back(i - '0');
        }
    }

    std::vector<int> sortedBlocks;
    int gap = 0;

    for (int i = 0; i < blocks.size(); ++i) {
        for (int j = 0; j < blocks[i]; ++j) {
            if (i % 2 == 1) {
                sortedBlocks.push_back(-1);
                ++gap;
            } else {
                sortedBlocks.push_back(i / 2);
            }
        }
    }

    std::vector<int> diskMap = sortedBlocks;

    int firstDot = 0;

    for (int i = sortedBlocks.size() - 1; i >= firstDot+2; --i) {
        if (sortedBlocks[i] != -1) {
            while (sortedBlocks[firstDot] != -1) {
                firstDot++;
            }
            sortedBlocks[firstDot] = sortedBlocks[i];
            sortedBlocks[i] = -1;
        }
    }

    __int128 checksum = 0;

    for (int i = 0; i < sortedBlocks.size(); ++i) {
        if (sortedBlocks[i] != -1) {
            checksum += static_cast<__int128>(sortedBlocks[i]) * i;
        }
    }

    std::cout << "disk checksum: ";
    printInt128(checksum);
    std::cout << std::endl;

    std::map<int, int> freeSpaces = findFreeSpaceSpans(diskMap);

    std::vector<int> filePositions(diskMap.size(), -1);
    for (int i = 0; i < diskMap.size(); ++i) {
        if (diskMap[i] != -1) {
            filePositions[diskMap[i]] = i;
        }
    }

    for (int fileID = blocks.size() - 1; fileID >= 0; --fileID) {
        if (fileID % 2 == 1) {
            continue;
        }

        int blockSize = blocks[fileID];
        int fileIDtoMove = fileID / 2;

        int filePos = filePositions[fileIDtoMove];
        if (filePos == -1) {
            continue;
        }

        for (auto space : freeSpaces) {
            if (space.second >= blockSize && filePos > space.first) {
                const int start = space.first;

                for (int& i : diskMap) {
                    if (i == fileIDtoMove) {
                        i = -1;
                    }
                }

                filePositions[fileIDtoMove] = -1;

                for (int i = start; i < start + blockSize; ++i) {
                    diskMap[i] = fileIDtoMove;
                    filePositions[fileIDtoMove] = i;
                }

                freeSpaces = findFreeSpaceSpans(diskMap);

                break;
            }
        }
    }

    checksum = 0;
    for (int i = 0; i < diskMap.size(); ++i) {
        if (diskMap[i] != -1) {
            checksum += static_cast<__int128>(diskMap[i]) * i;
        }
    }

    std::cout << "disk checksum by filesize: ";
    printInt128(checksum);
    std::cout << std::endl;

    return EXIT_SUCCESS;
}
