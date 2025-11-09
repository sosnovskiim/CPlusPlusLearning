#include "tasks_3.h"
#include <iostream>
#include <vector>
#include <utility>

using namespace std;

static pair<size_t, size_t> MatrixArgMax(const vector<vector<int>>& matrix) {
    size_t max_row = 0;
    size_t max_col = 0;
    int max_value = matrix[0][0];
    for (size_t i = 0; i < matrix.size(); i++) {
        for (size_t j = 0; j < matrix[i].size(); j++) {
            if (matrix[i][j] > max_value) {
                max_value = matrix[i][j];
                max_row = i;
                max_col = j;
            }
        }
    }
    return { max_row, max_col };
}

void task_307() {
    size_t n, k;
    cin >> n >> k;
    vector<vector<int>> matrix(n, vector<int>(k));
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < k; j++) {
            cin >> matrix[i][j];
        }
    }
    auto result = MatrixArgMax(matrix);
    cout << result.first << " " << result.second << endl;
}
