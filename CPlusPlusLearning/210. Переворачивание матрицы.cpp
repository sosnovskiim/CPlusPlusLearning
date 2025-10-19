#include "tasks_2.h"
#include <iostream>

static void reverse_rows(int a[][100], int n, int m) {
    for (int i = 0; i < n / 2; i++) {
        for (int j = 0; j < m; j++) {
            std::swap(a[i][j], a[n - 1 - i][j]);
        }
    }
}

void task_210() {
    int n, m;
    std::cin >> n >> m;

    int a[100][100];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            std::cin >> a[i][j];
        }
    }

    reverse_rows(a, n, m);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            std::cout << a[i][j] << " ";
        }
        std::cout << std::endl;
    }
}
