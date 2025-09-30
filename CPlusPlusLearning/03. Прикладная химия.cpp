#include "tasks_0.h"
#include <iostream>

void task_0_3() {
	int a, x, b, y;

	std::cin >> a;
	std::cin >> x;
	std::cin >> b;
	std::cin >> y;

	double salt_a = a * x * 0.01;
	double salt_b = b * y * 0.01;

	int result = (salt_a + salt_b) / (a + b) * 100;

	std::cout << result << std::endl;
}
