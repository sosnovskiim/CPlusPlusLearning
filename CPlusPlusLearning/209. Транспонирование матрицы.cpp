#include "tasks_2.h"
#include <iostream>

static void transpose(int a[][100], int n, int m, int t[][100]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            t[j][i] = a[i][j];
        }
    }
}

void task_209() {
    int n, m;
    std::cin >> n >> m;

    int a[100][100];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            std::cin >> a[i][j];
        }
    }

    int t[100][100];
    transpose(a, n, m, t);

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            std::cout << t[i][j] << " ";
        }
        std::cout << std::endl;
    }
}
