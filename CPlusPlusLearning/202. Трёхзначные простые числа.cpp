#include "tasks_2.h"
#include <iostream>

static bool is_prime(int n) {
	if (n % 2 == 0) {
		return false;
	}

	for (int i = 3; i <= std::sqrt(n); i += 2) {
		if (n % i == 0) {
			return false;
		}
	}

	return true;
}

void task_202() {
	for (int i = 100; i < 1000; i++) {
		if (is_prime(i)) {
			std::cout << i << " ";
		}
	}
	std::cout << std::endl;
}
