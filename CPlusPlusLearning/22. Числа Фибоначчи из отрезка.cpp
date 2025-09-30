#include "tasks_0.h"
#include <iostream>

void task_0_22() {
	int a, b;
	std::cin >> a >> b;

	int fib1 = 1, fib2 = 2;
	while (fib1 <= b) {
		if (fib1 >= a) {
			std::cout << fib1 << " ";
		}

		int next_fib = fib1 + fib2;
		fib1 = fib2;
		fib2 = next_fib;
	}
}
