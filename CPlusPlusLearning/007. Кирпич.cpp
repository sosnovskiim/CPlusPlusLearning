#include "tasks_0.h"
#include <iostream>

void task_007() {
	int a, b, x, y, z;

	std::cin >> a >> b;
	std::cin >> x >> y >> z;

	if (x <= a && y <= b || x <= b && y <= a ||
		y <= a && z <= b || y <= b && z <= a ||
		z <= a && x <= b || z <= b && x <= a) {
		std::cout << "Yes";
	} else {
		std::cout << "No";
	}
}
