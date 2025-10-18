#include "tasks_0.h"
#include <iostream>
#include <windows.h>

void task_012() {
	SetConsoleOutputCP(1251);

	int n;
	std::cout << "Введите двухзначное число: ";
	std::cin >> n;

	int d1 = n / 10;
	int d2 = n % 10;

	std::string result = ((d1 + d2) % 2 == 0) ? "чётная" : "нечётная";
	std::cout << "Сумма цифр " << result << std::endl;
}
