#include "tasks_3.h"
#include <iostream>
#include <vector>

using namespace std;

void task_306() {
    int m, n, k;
    cin >> m >> n >> k;
    vector<vector<char>> field(m, vector<char>(n, '0'));

    for (int i = 0; i < k; i++) {
        int x, y;
        cin >> x >> y;
        x--; y--;
        field[x][y] = '*';
    }

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (field[i][j] == '*') continue;

            int count = 0;
            for (int di = -1; di <= 1; di++) {
                for (int dj = -1; dj <= 1; dj++) {
                    if (di == 0 && dj == 0) continue;

                    int ni = i + di;
                    int nj = j + dj;

                    if (ni >= 0 && ni < m && nj >= 0 && nj < n) {
                        if (field[ni][nj] == '*') count++;
                    }
                }
            }

            if (count > 0) {
                field[i][j] = '0' + count;
            }
        }
    }

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cout << field[i][j];
            if (j < n - 1) cout << " ";
        }
        if (i < m - 1) cout << "\n";
    }
}
