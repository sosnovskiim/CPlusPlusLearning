#include "tasks_0.h"
#include <cmath>
#include <iostream>

void task_002() {
	int n, k, m;

	std::cin >> n;
	std::cin >> k;
	std::cin >> m;

	int t = k * m;
	int e = std::ceil(1. * n / t);
	int f = std::ceil(1. * (n - t * (e - 1)) / m);

	std::cout << e << " " << f << std::endl;
}
