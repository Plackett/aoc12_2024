#include <cmath>
#include <vector>
#include <iostream>
#include <sstream>
#include "inputData.h"

// THIS FUNCTION IS HANDWRITTEN FROM MY DECOMPILATION OF MY INPUT
int computeOutput(int &A, int &B, int &C) {
    B = (A % 8) ^ (A >> B) ^ C; // Compute B
    const int output = B % 8;   // Output based on B
    C = A >> 3;                 // Update C
    A = A >> 3;                 // Update A
    return output;
}

int predictAForOutput(const std::vector<int> &desiredOutput) {
    int A = 0;
    int B = 0, C = 0;

    // Work backwards through the output sequence
    for (int i = desiredOutput.size() - 1; i >= 0; --i) {
        const int targetOutput = desiredOutput[i];
        bool found = false;

        // Debug: Print target output and current state
        std::cerr << "Target Output: " << targetOutput << " | Current A: " << A
                  << ", B: " << B << ", C: " << C << "\n";

        // Search for a candidate value of A that matches the output
        for (int candidateA = 0; candidateA < INT_MAX; candidateA += 256) { // Wider range
            int tempA = candidateA, tempB = B, tempC = C;

            if (const int output = computeOutput(tempA, tempB, tempC); output == targetOutput) {
                A = candidateA;  // Update A to candidate value
                B = tempB;       // Persist changes to B
                C = tempC;       // Persist changes to C
                found = true;
                break;
            }
        }

        if (!found) {
            std::cerr << "Failed to find A for output " << targetOutput << "\n";
            return -1;
        }
    }

    return A;
}

struct RegisterObject {
    long long A, B, C;
};

long long getCombo(const int operand, const RegisterObject &reg) {
    if (operand > 6)
        std::exit(-1);
    if (operand == 4)
        return reg.A;
    if (operand == 5)
        return reg.B;
    if (operand == 6)
        return reg.C;
    return operand;
}

std::vector<int> runProgram( const std::vector<int>& operations, const RegisterObject& registers, const bool print ) {
    int currentInstruction = 0;
    std::vector<int> results;
    RegisterObject reg = registers;
    bool first = true;
    while (currentInstruction < operations.size()) {
        const int operand = operations[currentInstruction + 1];
        switch (operations[currentInstruction]) {
            case 0: { // adv
                reg.A = reg.A / std::pow(2, getCombo(operand, reg));
                break;
            }
            case 1: { // bxl
                reg.B ^= operand;
                break;
            }
            case 2: { // bst
                reg.B = getCombo(operand, reg) % 8;
                break;
            }
            case 3: { // jnz
                if (reg.A != 0) {
                    currentInstruction = operand;
                    continue;
                }
                break;
            }
            case 4: { // bxc
                reg.B ^= reg.C;
                break;
            }
            case 5: { // out
                const long long value = getCombo(operand, reg) % 8;

                if(print) {
                    if (!first) {
                        std::cout << ",";
                    }
                    std::cout << value;
                    first = false;
                }
                results.push_back(static_cast<int>(value));
                break;
            }
            case 6: { // bdv
                reg.B = reg.A / std::pow(2,getCombo(operand, reg));
                break;
            }
            case 7: { // cdv
                reg.C = reg.A / std::pow(2,getCombo(operand, reg));
                break;
            }
            default:
                break;
        }

        currentInstruction += 2;
    }

    return results;
}

int main() {
    std::stringstream file = readInputData(17);
    std::string line;
    std::vector<int> operations{};
    RegisterObject regs{-1, -1, -1};

    while (std::getline(file, line)) {
        if (line.find("A:") != std::string::npos) {
            regs.A = std::stoll(line.substr(line.find(':') + 1));
        }
        if (line.find("B:") != std::string::npos) {
            regs.B = std::stoll(line.substr(line.find(':') + 1));
        }
        if (line.find("C:") != std::string::npos) {
            regs.C = std::stoll(line.substr(line.find(':') + 1));
        }
        if (line.find("Program") != std::string::npos) {
            std::stringstream ss(line.substr(line.find(':') + 1));
            std::string operand;
            while (std::getline(ss, operand, ',')) {
                operations.push_back(std::stoi(operand));
            }
        }
    }

    auto desiredOutputs = runProgram(operations, regs, true);
    std::cout << "\n";

    if (int predictedA = predictAForOutput(desiredOutputs); predictedA != -1) {
        std::cout << "Value of A for program to output itself: " << predictedA << std::endl;
    } else {
        std::cout << "Failed to predict A.\n";
    }

    return EXIT_SUCCESS;
}