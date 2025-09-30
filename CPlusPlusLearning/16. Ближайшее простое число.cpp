#include "tasks_0.h"
#include <iostream>

bool is_prime(int n) {
	if (n % 2 == 0) {
		return false;
	}

	for (int i = 3; i * i <= n; i += 2) {
		if (n % i == 0) {
			return false;
		}
	}

	return true;
}

void task_0_16() {
	int n;
	std::cin >> n;

	if (is_prime(n)) {
		std::cout << n << std::endl;
		return;
	}

	int prev = n - 1;
	int next = n + 1;
	while (true) {
		bool is_prev_prime = is_prime(prev);
		bool is_next_prime = is_prime(next);

		if (is_prev_prime && is_next_prime) {
			if ((n - prev) <= (next - n)) {
				std::cout << prev << std::endl;
			} else {
				std::cout << next << std::endl;
			}
			break;
		} else if (is_prev_prime) {
			std::cout << prev << std::endl;
			break;
		} else if (is_next_prime) {
			std::cout << next << std::endl;
			break;
		}

		prev--;
		next++;
	}
}
