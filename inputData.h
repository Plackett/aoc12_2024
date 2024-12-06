#ifndef INPUTDATA_H
#define INPUTDATA_H
#include <fstream>
#include <sstream>
#include <iostream>

inline std::stringstream readInputData(const int day) {
	std::string fileName = "input";
	fileName += std::to_string(day);
	fileName += ".txt";
	std::ifstream file(fileName);
	if(!file.is_open()) {
		std::cerr << "Could not open input" << day << ".txt! Please try again." << std::endl;
		std::exit(EXIT_FAILURE);
	}
	std::stringstream buffer;
	buffer << file.rdbuf();
	return buffer;
}

#endif //INPUTDATA_H
