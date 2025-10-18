#include "tasks_0.h"
#include <fstream>
#include <string>

void task_027() {
	std::ifstream input("in.txt");
	std::ofstream output("out.txt");

	std::string line;
	while (getline(input, line)) {
		size_t pos = line.find('(');

		if (pos != std::string::npos) {
			output << line.substr(0, pos) << std::endl;
		} else {
			output << line << std::endl;
		}
	}

	input.close();
	output.close();
}
