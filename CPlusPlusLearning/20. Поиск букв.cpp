#include "tasks_0.h"
#include <iostream>
#include <string>

void task_0_20() {
	std::string s;
	char c1, c2;

	getline(std::cin, s);
	std::cin >> c1 >> c2;

	int i1 = -1, i2 = -1;
	for (int i = 0; i < s.length(); i++) {
		if (s[i] == c1) {
			i1 = i;
		} else if (s[i] == c2) {
			i2 = i;
		}
	}

	if (i1 > i2) {
		std::cout << c1 << std::endl;
	} else {
		std::cout << c2 << std::endl;
	}
}
