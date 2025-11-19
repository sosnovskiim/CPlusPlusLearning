#include "tasks_3.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <numeric>
#include <windows.h>

using namespace std;

static struct Point {
    int x, y;
};

static bool is_in_circle(const Point& p) {
    return p.x * p.x + p.y * p.y <= 100;
}

static double distance_from_origin(const Point& p) {
    return sqrt(p.x * p.x + p.y * p.y);
}

static bool has_multiple_coordinates(const Point& p) {
    return (p.x != 0 && p.y % p.x == 0) || (p.y != 0 && p.x % p.y == 0);
}

static bool compare_points(const Point& a, const Point& b) {
    if (a.x == b.x) {
        return a.y > b.y;
    }
    return a.x < b.x;
}

static vector<Point> filter_points_in_circle(const vector<Point>& points) {
    vector<Point> result;
    copy_if(points.begin(), points.end(), back_inserter(result), is_in_circle);
    return result;
}

static double sum_of_distances(const vector<Point>& points) {
    return accumulate(points.begin(), points.end(), 0.0,
        [](double sum, const Point& p) {
            return sum + distance_from_origin(p);
        });
}

static vector<Point> find_points_with_multiple_coordinates(const vector<Point>& points) {
    vector<Point> result;
    copy_if(points.begin(), points.end(), back_inserter(result), has_multiple_coordinates);
    return result;
}

static void sort_points(vector<Point>& points) {
    sort(points.begin(), points.end(), compare_points);
}

static void print_points(const vector<Point>& points) {
    for (const auto& p : points) {
        cout << p.x << " " << p.y << endl;
    }
}

void task_311() {
    SetConsoleOutputCP(1251);

    vector<Point> points = {
        {3, 4}, {10, 10}, {0, 5}, {6, 8}, {2, 4},
        {1, 1}, {10, 11}, {5, 0}, {3, 9}, {4, 2}
    };
    cout << "Исходные точки:" << endl;
    print_points(points);

    cout << "\nТочки в окружности радиуса 10" << endl;
    print_points(filter_points_in_circle(points));

    cout << "\nСумма расстояний до начала координат: " << sum_of_distances(points) << endl;

    cout << "\nТочки с кратными координатами" << endl;
    print_points(find_points_with_multiple_coordinates(points));

    cout << "\nОтсортированные точки в порядке возрастания x и убывывания y" << endl;
    sort_points(points);
    print_points(points);
}
