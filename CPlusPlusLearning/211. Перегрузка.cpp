#include "tasks_2.h"
#include <iostream>
#include <windows.h>

static float f(float x) {
	if (x < 0) {
		return -4;
	}
	if (x >= 0 && x < 1) {
		return x * x + 3 * x + 4;
	}
	return 2;
}

static void f(float x, float& y) {
	if (x < 0) {
		y = -4;
	} else if (x >= 0 && x < 1) {
		y = x * x + 3 * x + 4;
	} else {
		y = 2;
	}
}

void task_211() {
	SetConsoleOutputCP(1251);

	float x1 = -0.5, x2 = 0, x3 = 0.5, x4 = 1;

	float y1 = f(x1), y2 = f(x2), y3 = f(x3), y4 = f(x4);
	std::cout << "Возврат значения:" << std::endl;
	std::cout << "f(" << x1 << ") = " << y1 << std::endl;
	std::cout << "f(" << x2 << ") = " << y2 << std::endl;
	std::cout << "f(" << x3 << ") = " << y3 << std::endl;
	std::cout << "f(" << x4 << ") = " << y4 << std::endl;

	f(x1, y1); f(x2, y2); f(x3, y3); f(x4, y4);
	std::cout << "Передача значения по ссылке:" << std::endl;
	std::cout << "f(" << x1 << ") = " << y1 << std::endl;
	std::cout << "f(" << x2 << ") = " << y2 << std::endl;
	std::cout << "f(" << x3 << ") = " << y3 << std::endl;
	std::cout << "f(" << x4 << ") = " << y4 << std::endl;
}
