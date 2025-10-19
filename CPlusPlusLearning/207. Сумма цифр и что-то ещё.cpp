#include "tasks_2.h"
#include <iostream>

static int find_digit_sums_equals_k(int n, int k, int result[]) {
    int cnt = 0;
    for (int i = 1; i < n; i++) {
        if (i / 10 + i % 10 == k) {
            result[cnt] = i;
            cnt++;
        }
    }
    return cnt;
}

void task_207() {
    int t;
    std::cin >> t;

    int array_n[20];
    for (int i = 0; i < t; i++) {
        std::cin >> array_n[i];
    }

    int array_k[20];
    for (int i = 0; i < t; i++) {
        std::cin >> array_k[i];
    }

    for (int i = 0; i < t; i++) {
        int n = array_n[i];
        int k = array_k[i];
        int result[20];
        int cnt = find_digit_sums_equals_k(n, k, result);

        std::cout << cnt << std::endl;
        for (int j = 0; j < cnt; j++) {
            std::cout << result[j] << " ";
        }
        std::cout << std::endl;
    }
}
