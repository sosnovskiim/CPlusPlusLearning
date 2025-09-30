#include "tasks_0.h"
#include <iomanip>
#include <iostream>

void task_0_24() {
	int n;
	std::cin >> n;
	double sum = 0;
	bool is_first_found = false;
	bool is_second_found = false;

	for (int i = 0; i < n; i++) {
		double a;
		std::cin >> a;

		if (a < 0) {
			if (!is_first_found) {
				is_first_found = true;
			} else if (!is_second_found) {
				is_second_found = true;
			}
		} else if (is_first_found && !is_second_found) {
			sum += a;
		}
	}

	if (is_first_found && is_second_found) {
		std::cout << std::fixed << std::setprecision(3);
		std::cout << sum << std::endl;
	} else {
		std::cout << 0 << std::endl;
	}
}
