#include "tasks_0.h"
#include <iomanip>
#include <iostream>

void task_0_8() {
	int a, b, c;

	std::cin >> a >> b >> c;

	if (a + b > c && a + c > b && b + c > a) {
		double p = (a + b + c) / 2.;

		double s = std::sqrt(p * (p - a) * (p - b) * (p - c));

		std::cout << std::fixed << std::setprecision(6);
		std::cout << s << std::endl;
	} else {
		std::cout << -1 << std::endl;
	}
}
