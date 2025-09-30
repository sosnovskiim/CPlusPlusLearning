#include "tasks_0.h"
#include <iostream>
#include <string>

void task_0_17() {
	std::string s;
	getline(std::cin, s);

	int cnt = 0;
	for (char c : s) {
		if (isdigit(c)) {
			cnt++;
		}
	}

	std::cout << cnt << std::endl;
}
