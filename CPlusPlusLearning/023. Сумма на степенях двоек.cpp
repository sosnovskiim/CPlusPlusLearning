#include "tasks_0.h"
#include <iostream>

void task_023() {
	int n;
	std::cin >> n;

	int sum = 0, pow = 1;
	for (int i = 1; i <= n; i++) {
		int a;
		std::cin >> a;

		if (pow == i) {
			sum += a;
			pow *= 2;
		}
	}

	std::cout << sum << std::endl;
}
