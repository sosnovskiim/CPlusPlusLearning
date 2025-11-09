#include "tasks_3.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

void task_305() {
    int n;
    cin >> n;
    vector<pair<int, int>> points(n);

    for (int i = 0; i < n; i++) {
        cin >> points[i].first >> points[i].second;
    }

    sort(points.begin(), points.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
        int dist_a = a.first * a.first + a.second * a.second;
        int dist_b = b.first * b.first + b.second * b.second;
        return dist_a < dist_b;
    });

    for (const auto& point : points) {
        cout << point.first << " " << point.second << endl;
    }
}
