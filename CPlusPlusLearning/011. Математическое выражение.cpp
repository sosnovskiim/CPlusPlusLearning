#include "tasks_0.h"
#include <cmath>
#include <iomanip>
#include <iostream>
#include <windows.h>

static double expr(double x, double y) {
	return (1 + std::sin(std::sqrt(x + 1))) / std::cos(12 * y - 4);
}

void task_011() {
	SetConsoleOutputCP(1251);
	std::cout << std::fixed << std::setprecision(6);
	std::cout << "Большой по модулю: " << expr(1.467401, 0.2024336) << std::endl;
	std::cout << "Близкий к нулю: " << expr(21., 0.3333) << std::endl;
	std::cout << "Целое число: " << expr(-1., 0.3333) << std::endl;
}
