#ifndef INPUTDATA_H
#define INPUTDATA_H
#include <fstream>

inline std::ifstream readInputData(const int day) {
	std::string fileName = "input";
	fileName += std::to_string(day);
	fileName += ".txt";
	std::ifstream file(fileName);
	if(!file.is_open()) {
		std::cerr << "Could not open input" << day << ".txt! Please try again." << std::endl;
		std::exit(EXIT_FAILURE);
	}
	return file;
}

#endif //INPUTDATA_H
