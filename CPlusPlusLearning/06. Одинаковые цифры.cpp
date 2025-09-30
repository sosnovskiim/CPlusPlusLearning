#include "tasks_0.h"
#include <iostream>

void task_0_6() {
	int n;
	std::cin >> n;

	int d1 = n / 100;
	int d2 = n / 10 % 10;
	int d3 = n % 10;

	if (d1 == d2 || d2 == d3 || d1 == d3) {
		std::cout << "YES" << std::endl;
	} else {
		std::cout << "NO" << std::endl;
	}
}
