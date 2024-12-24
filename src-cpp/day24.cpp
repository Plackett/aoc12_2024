#include <map>
#include <queue>
#include <cmath>

#include "inputData.h"

struct operation {
	std::string operandOne;
	std::string opcode;
	std::string operandTwo;
	std::string result;
};

int runOperation(const operation &op, const int existingOne, const int existingTwo) {
	if(op.opcode == "AND") {
		return existingOne & existingTwo;
	}
	if(op.opcode == "OR") {
		return existingOne | existingTwo;
	}
	return existingOne ^ existingTwo;
}

int main() {
	std::stringstream file = readInputData(24);
	std::string line;
	std::vector<operation> toProcess{};
	std::map<std::string,int> variables{};
	while (std::getline(file, line)) {
		if(line.find(':') != std::string::npos) {
			variables.emplace(line.substr(0, line.find(':')),std::stoi(line.substr(line.find(':')+1)));
		} else if(!line.empty()) {
			operation current{};
			std::stringstream ss(line);
			std::string token;
			int counter = 0;
			while(std::getline(ss,token, ' ')) {
				if(counter == 0) {
					current.operandOne = token;
					counter++;
				} else if(counter == 1) {
					current.opcode = token;
					counter++;
				} else if(counter == 2) {
					current.operandTwo = token;
					counter++;
				} else if(counter == 3) counter ++;
				else {
					current.result = token;
				}
			}
			toProcess.push_back(current);
		}
	}
	std::vector zDigits(1000,0);
	while(toProcess.size() > 0) {
		for(int i = 0; i < toProcess.size(); i++) {
			if(variables.find(toProcess[i].operandOne) != variables.end() && variables.find(toProcess[i].operandTwo) != variables.end()) {
				int operandOne = variables[toProcess[i].operandOne];
				int operandTwo = variables[toProcess[i].operandTwo];
				if(variables.find(toProcess[i].result) != variables.end()) {
					variables.at(toProcess[i].result) = runOperation(toProcess[i],operandOne,operandTwo);
				} else {
					variables.emplace(toProcess[i].result,runOperation(toProcess[i],operandOne,operandTwo));
				}
				toProcess.erase(toProcess.begin()+i);
			}
		}
	}
	for(auto&[fst, snd] : variables) {
		if(fst.at(0) == 'z') {
			zDigits[std::stoi(fst.substr(1))] = snd;
		}
	}
	long long result = 0;
	for(int i = 0; i < zDigits.size(); i++) {
		if(zDigits.at(i) == 1) {
			result += std::pow(2,i);
		}
	}
	std::cout << "final result = " << result << std::endl;
	return EXIT_SUCCESS;
}