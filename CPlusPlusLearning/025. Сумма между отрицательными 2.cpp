#include "tasks_0.h"
#include <iomanip>
#include <iostream>

void task_025() {
	int n;
	std::cin >> n;
	double sum = 0;
	double cur_sum = 0;
	bool is_first_found = false;
	bool is_last_found = false;

	for (int i = 0; i < n; i++) {
		double a;
		std::cin >> a;

		if (a < 0) {
			if (!is_first_found) {
				is_first_found = true;
			} else {
				is_last_found = true;
				sum = cur_sum;
				cur_sum += a;
			}
		} else if (is_first_found) {
			cur_sum += a;
		}
	}

	if (is_first_found && is_last_found) {
		std::cout << std::fixed << std::setprecision(3);
		std::cout << sum << std::endl;
	}
	else {
		std::cout << 0 << std::endl;
	}
}
