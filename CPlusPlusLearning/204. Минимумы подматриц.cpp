#include "tasks_2.h"
#include <iostream>

static int find_submatrix_min(int a[][20], int n, int k) {
    int mn = INT_MAX;
    for (int i = k; i < n; i++) {
        for (int j = k; j < n; j++) {
            if (a[i][j] < mn) {
                mn = a[i][j];
            }
        }
    }
    return mn;
}

void task_204() {
    int n;
    std::cin >> n;

    int a[20][20];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            std::cin >> a[i][j];
        }
    }

    int b[20];
    for (int k = 0; k < n; k++) {
        b[k] = find_submatrix_min(a, n, k);
    }

    for (int k = 0; k < n; k++) {
        std::cout << b[k] << " ";
    }
    std::cout << std::endl;
}
