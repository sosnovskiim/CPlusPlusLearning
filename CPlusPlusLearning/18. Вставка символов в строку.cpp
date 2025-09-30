#include "tasks_0.h"
#include <iostream>
#include <string>

void task_0_18() {
	char c1, c2;
	std::string s;

	std::cin >> c1 >> c2;
	std::cin.get();
	getline(std::cin, s);

	std::string result = "";
	for (char c : s) {
		result += c;

		if (c == c2) {
			result += c1;
		}
	}

	std::cout << result << std::endl;
}
