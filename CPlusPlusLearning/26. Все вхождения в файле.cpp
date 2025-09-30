#include "tasks_0.h"
#include <fstream>
#include <string>

void task_0_26() {
	std::ifstream input("in.txt");
	std::ofstream output("out.txt");

	std::string line;
	while (getline(input, line)) {
		std::string result;
		size_t pos = 0, found = 0;

		while ((found = line.find("main", pos)) != std::string::npos) {
			result += line.substr(pos, found - pos);
			result += "\"main\"";
			pos = found + 4;
		}

		result += line.substr(pos);
		output << result << std::endl;
	}

	input.close();
	output.close();
}
