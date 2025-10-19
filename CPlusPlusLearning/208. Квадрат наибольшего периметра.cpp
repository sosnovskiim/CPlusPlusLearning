#include "tasks_2.h"
#include <iomanip>
#include <iostream>

static double distance_between_points(int x1, int y1, int x2, int y2) {
    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

static bool isSquare(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4) {
    double d12 = distance_between_points(x1, y1, x2, y2);
    double d13 = distance_between_points(x1, y1, x3, y3);
    double d14 = distance_between_points(x1, y1, x4, y4);
    
    if (d12 == d13 && d12 * sqrt(2) == d14) {
        double d24 = distance_between_points(x2, y2, x4, y4);
        double d34 = distance_between_points(x3, y3, x4, y4);
        return d24 == d12 && d34 == d12;
    }

    if (d12 == d14 && d12 * sqrt(2) == d13) {
        double d23 = distance_between_points(x2, y2, x3, y3);
        double d34 = distance_between_points(x3, y3, x4, y4);
        return d23 == d12 && d34 == d12;
    }

    if (d13 == d14 && d13 * sqrt(2) == d12) {
        double d23 = distance_between_points(x2, y2, x3, y3);
        double d24 = distance_between_points(x2, y2, x4, y4);
        return d23 == d13 && d24 == d13;
    }

    return false;
}

static double get_square_perimeter(double a) {
    return 4 * a;
}

void task_208() {
    int n;
    std::cin >> n;
    int x[30], y[30];
    for (int i = 0; i < n; i++) {
        std::cin >> x[i] >> y[i];
    }

    double mxp = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            for (int k = j + 1; k < n; k++) {
                for (int l = k + 1; l < n; l++) {
                    if (isSquare(x[i], y[i], x[j], y[j], x[k], y[k], x[l], y[l])) {
                        double a = distance_between_points(x[i], y[i], x[j], y[j]);
                        double p = get_square_perimeter(a);
                        if (p > mxp) {
                            mxp = p;
                        }
                    }
                }
            }
        }
    }
    std::cout << std::fixed << std::setprecision(3) << mxp << std::endl;
}
