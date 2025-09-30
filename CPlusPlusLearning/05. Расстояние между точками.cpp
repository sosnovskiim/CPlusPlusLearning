#include "tasks_0.h"
#include <cmath>
#include <iomanip>
#include <iostream>

void task_0_5() {
	double x1, y1, x2, y2;

	std::cin >> x1 >> y1;
	std::cin >> x2 >> y2;

	double d = std::sqrt(std::pow(x1 - x2, 2) + std::pow(y1 - y2, 2));

	std::cout << std::fixed << std::setprecision(4);
	std::cout << d << std::endl;
}
