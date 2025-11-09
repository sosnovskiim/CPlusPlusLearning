#include "tasks_3.h"
#include <iostream>
#include <vector>

using namespace std;

static vector<vector<int>> Transpose(const vector<vector<int>>& matrix) {
    size_t m = matrix.size();
    size_t n = matrix[0].size();
    vector<vector<int>> result(n, vector<int>(m));
    for (size_t i = 0; i < m; i++) {
        for (size_t j = 0; j < n; j++) {
            result[j][i] = matrix[i][j];
        }
    }
    return result;
}

static void PrintMatrix(const vector<vector<int>>& matrix) {
    for (const auto& row : matrix) {
        for (size_t j = 0; j < row.size(); j++) {
            cout << row[j];
            if (j < row.size() - 1) {
                cout << " ";
            }
        }
        cout << endl;
    }
}

void task_309() {
    vector<vector<int>> test = {
        {1, 2, 3},
        {4, 5, 6}
    };
    PrintMatrix(test);
    PrintMatrix(Transpose(test));
}
