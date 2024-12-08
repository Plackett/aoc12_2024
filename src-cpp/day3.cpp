#include <iostream>
#include <vector>

#include "inputData.h"

int main() {
	std::stringstream file = readInputData(3);
	std::string line;
	int sum = 0;
	int sumparttwo = 0;
	bool enabled = true;
	while(std::getline(file,line)) {
		for(int i = 0; i < line.size() - 8; i++) {
			if(line[i] == 'm' && line[i+1] == 'u' && line[i+2] == 'l' && line[i+3] == '(') {
				int first = 0, second = 0;
				for(int j = i+4; j < line.size(); j++) {
					if(line[j] == ',') {
						first = std::stoi(line.substr(i+4, j-i-4));
						for(int k = j+1; k < line.size(); k++) {
							if(line[k] == ')') {
								second = std::stoi(line.substr(j+1, k-j-1));
								break;
							}
							if(!isalnum(line[k]) || isspace(line[k]))
								break;
						}
						break;
					}
					if(!isalnum(line[j]) || isspace(line[j]) )
						break;

				}
				sum += first * second;
			}
		}
		for(int i = 0; i < line.size() - 8; i++) {
			if(line[i] == 'm' && line[i+1] == 'u' && line[i+2] == 'l' && line[i+3] == '(' && enabled) {
				int first = 0, second = 0;
				for(int j = i+4; j < line.size(); j++) {
					if(line[j] == ',') {
						first = std::stoi(line.substr(i+4, j-i-4));
						for(int k = j+1; k < line.size(); k++) {
							if(line[k] == ')') {
								second = std::stoi(line.substr(j+1, k-j-1));
								break;
							}
							if(!isalnum(line[k]) || isspace(line[k]))
								break;
						}
						break;
					}
					if(!isalnum(line[j]) || isspace(line[j]) )
						break;

				}
				sumparttwo += first * second;
			}
			if(line[i] == 'd' && line[i+1] == 'o' && line[i+2] == '(' && line[i+3] == ')')
				enabled = true;
			if(line[i] == 'd' && line[i+1] == 'o' && line[i+2] == 'n' && line[i+3] == '\'' && line[i+4] == 't' && line[i+5] == '(' && line[i+6] == ')')
				enabled = false;
		}
	}
	std::cout << "Sum of proper mul operations: " << sum << std::endl;
	std::cout << "Sum of proper mul operations with do/dont: " << sumparttwo << std::endl;
	return EXIT_SUCCESS;
}