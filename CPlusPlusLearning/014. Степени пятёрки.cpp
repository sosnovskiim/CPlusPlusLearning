#include "tasks_0.h"
#include <iostream>

bool is_power_of_five(int a) {
	while (a > 1) {
		if (a % 5 != 0) {
			return false;
		}
		a /= 5;
	}
	return true;
}

void task_014() {
	int n;
	std::cin >> n;
	int cnt = 0;

	for (int i = 0; i < n; i++) {
		int a;
		std::cin >> a;

		if (is_power_of_five(a)) {
			cnt++;
		}
	}
	std::cout << cnt << std::endl;
}
