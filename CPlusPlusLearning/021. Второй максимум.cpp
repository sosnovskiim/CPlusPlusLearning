#include "tasks_0.h"
#include <iostream>

void task_021() {
	int n;
	std::cin >> n;

	int max1 = -101, max2 = -101;
	for (int i = 0; i < n; i++) {
		int a;
		std::cin >> a;

		if (a > max1) {
			max2 = max1;
			max1 = a;
		} else if (a > max2 && a < max1) {
			max2 = a;
		}
	}

	std::cout << max2 << std::endl;
}
