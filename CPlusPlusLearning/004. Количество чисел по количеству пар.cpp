#include "tasks_0.h"
#include <cmath>
#include <iostream>

void task_004() {
	int m;
	std::cin >> m;
	int n = (1 + std::sqrt(1 + 8 * m)) / 2;
	std::cout << n << std::endl;
}
