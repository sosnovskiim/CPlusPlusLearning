#include "tasks_0.h"
#include <iostream>

void task_0_9() {
	int n;
	std::cin >> n;
	int result = ((n % 3 == 0) != (n % 10 == 3));
	std::cout << result << std::endl;
}
