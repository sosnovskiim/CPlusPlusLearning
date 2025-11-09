#include "tasks_2.h"
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>

static double distance_between_points(int x1, int y1, int x2, int y2) {
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

static double get_square_perimeter(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4) {
    std::vector<std::pair<int, int>> p = { {x1, y1}, {x2, y2}, {x3, y3}, {x4, y4} };

    std::vector<double> d;
    for (int i = 0; i < 4; i++) {
        for (int j = i + 1; j < 4; j++) {
            d.push_back(distance_between_points(p[i].first, p[i].second, p[j].first, p[j].second));
        }
    }

    std::sort(begin(d), end(d));

    double eps = 1e-9;
    bool is_sides_equal = fabs(d[0] - d[1]) < eps && fabs(d[0] - d[2]) < eps && fabs(d[0] - d[3]) < eps;
    bool is_diagonals_equal = fabs(d[4] - d[5]) < eps;
    bool is_correct_ratio = fabs(d[4] - d[0] * sqrt(2)) < eps;

    if (is_sides_equal && is_diagonals_equal && is_correct_ratio) {
        return d[0] * 4;
    }
    return 0;
}

void task_208() {
    int n;
    std::cin >> n;

    std::vector<int> x(n), y(n);
    for (int i = 0; i < n; i++) {
        std::cin >> x[i] >> y[i];
    }

    double mxp = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            for (int k = j + 1; k < n; k++) {
                for (int l = k + 1; l < n; l++) {
                    double p = get_square_perimeter(x[i], y[i], x[j], y[j], x[k], y[k], x[l], y[l]);
                    if (p > mxp) {
                        mxp = p;
                    }
                }
            }
        }
    }

    if (mxp > 0) {
        std::cout << std::fixed << std::setprecision(4) << mxp << std::endl;
    }
    else {
        std::cout << 0 << std::endl;
    }
}
