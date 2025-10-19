#include "tasks_2.h"
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <windows.h>

using namespace std;

static int damerau_levenshtein(const string& str1, const string& str2) {
    int len1 = str1.length();
    int len2 = str2.length();
    vector<vector<int>> dp(len1 + 1, vector<int>(len2 + 1, 0));

    for (int i = 0; i <= len1; i++) {
        dp[i][0] = i;
    }
    for (int j = 0; j <= len2; j++) {
        dp[0][j] = j;
    }

    for (int i = 1; i <= len1; i++) {
        for (int j = 1; j <= len2; j++) {
            int cost = (str1[i - 1] == str2[j - 1]) ? 0 : 1;

            dp[i][j] = min(dp[i - 1][j] + 1, min(dp[i][j - 1] + 1, dp[i - 1][j - 1] + cost));

            if (i > 1 && j > 1 && str1[i - 1] == str2[j - 2] && str1[i - 2] == str2[j - 1]) {
                dp[i][j] = min(dp[i][j], dp[i - 2][j - 2] + cost);
            }
        }
    }

    return dp[len1][len2];
}

static int max_damerau_levenshtein(const string& str1, const string& str2, const string& str3) {
    return max(damerau_levenshtein(str1, str2), max(damerau_levenshtein(str1, str3), damerau_levenshtein(str2, str3)));
}

static int** create_matrix(int n, int m) {
    int** a = new int* [n];
    for (int i = 0; i < n; i++) {
        a[i] = new int[m];
    }

    int cnt = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            a[i][j] = cnt++;
        }
    }

    return a;
}

static void print_matrix(int** a, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            std::cout << a[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

static void cyclic_shift_rows(int** a, int n, int m) {
    if (n <= 1) {
        return;
    }
    int* temp = new int[m];

    for (int j = 0; j < m; j++) {
        temp[j] = a[n - 1][j];
    }
    for (int i = n - 1; i > 0; i--) {
        for (int j = 0; j < m; j++) {
            a[i][j] = a[i - 1][j];
        }
    }
    for (int j = 0; j < m; j++) {
        a[0][j] = temp[j];
    }

    delete[] temp;
}

static int get_prime_divisors(int n, int divisors[], int size) {
    if (n <= 1) {
        return 0;
    }

    int cnt = 0;
    if (n % 2 == 0) {
        divisors[cnt++] = 2;
        while (n % 2 == 0) {
            n /= 2;
        }
    }

    for (int i = 3; i * i <= n && cnt < size; i += 2) {
        if (n % i == 0) {
            divisors[cnt++] = i;
            while (n % i == 0) {
                n /= i;
            }
        }
    }

    if (n > 1 && cnt < size) {
        divisors[cnt++] = n;
    }

    return cnt;
}

void task_201() {
    SetConsoleOutputCP(1251);

    cout << "1. Максимальное расстояние Дамерау-Левенштейна между строками" << endl;
    string str1 = "abc", str2 = "acb", str3 = "abcd";
    cout << "\nПример: '" << str1 << "', '" << str2 << "', '" << str3 << "'" << endl;
    cout << "\nМежду '" << str1 << "' и '" << str2 << "' расстояние " << damerau_levenshtein(str1, str2) << endl;
    cout << "Между '" << str1 << "' и '" << str3 << "' расстояние " << damerau_levenshtein(str1, str3) << endl;
    cout << "Между '" << str2 << "' и '" << str3 << "' расстояние " << damerau_levenshtein(str2, str3) << endl;
    cout << "\nОтвет: " << max_damerau_levenshtein(str1, str2, str3) << endl;

    cout << "\n\n2. Циклический сдвиг строк" << endl;
    int n = 3, m = 4;
    int** a = create_matrix(n, m);
    cout << "\nМассив до изменения:" << endl;
    print_matrix(a, n, m);
    cyclic_shift_rows(a, n, m);
    cout << "\nМассив после изменения:" << endl;
    print_matrix(a, n, m);

    cout << "\n\n3. Простые делители числа" << endl;
    int number = 1105;
    int divisors[20];
    int size = get_prime_divisors(number, divisors, 20);
    cout << "\nПример: " << number << endl;
    cout << "Делители: ";
    for (int i = 0; i < size; i++) {
        cout << divisors[i] << " ";
    }
    cout << endl;
}
