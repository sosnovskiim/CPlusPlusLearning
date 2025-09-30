#include "tasks_0.h"
#include <iomanip>
#include <iostream>

void task_0_13() {
	double a;
	double sum = 0;
	int sign = -1;
	int cnt = 1;
	bool is_negative = false;

	while (std::cin >> a) {
		if (a < 0 && !is_negative) {
			is_negative = true;
		}
		if (!is_negative) {
			sum += sign * a / cnt;
			sign = -sign;
			cnt++;
		}
	}

	std::cout << std::fixed << std::setprecision(6);
	std::cout << sum << std::endl;
}
