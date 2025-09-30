#include "tasks_0.h"
#include <iostream>

void task_0_15() {
	int o;
	std::cin >> o;
	int i = 1;

	for (int cnt = 1; cnt < o; cnt += i) {
		i++;
	}

	std::cout << i << std::endl;
}
