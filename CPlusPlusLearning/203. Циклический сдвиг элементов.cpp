#include "tasks_2.h"
#include <iostream>

static void cyclic_shift(int a[], int n) {
    if (n <= 1) {
        return;
    }

    int first = a[0];

    for (int i = 0; i < n - 1; i++) {
        a[i] = a[i + 1];
    }

    a[n - 1] = first;
}

void task_203() {
    int n, m;
    std::cin >> n >> m;

    int a[20][20];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            std::cin >> a[i][j];
        }
    }

    for (int i = 0; i < n; i++) {
        cyclic_shift(a[i], m);
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            std::cout << a[i][j];
            if (j < m - 1) {
                std::cout << " ";
            }
        }
        std::cout << std::endl;
    }
}
