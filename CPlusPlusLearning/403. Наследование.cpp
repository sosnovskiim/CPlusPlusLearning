#include "tasks_4.h"
#include <iostream>
#include <vector>
#include <memory>
#include <cmath>
#include <windows.h>

using namespace std;

static class Function {

public:
    virtual double calculate(double x) const = 0;
    virtual void printInfo() const = 0;
};

static class Line : public Function {

private:
    double a, b;

public:
    Line(double a_val = 1.0, double b_val = 0.0) : a(a_val), b(b_val) {}

    double calculate(double x) const override {
        return a * x + b;
    }

    void printInfo() const override {
        cout << "Линейная функция: y = ";
        if (a != 0) {
            if (a != 1) cout << a;
            cout << "x";
        }
        if (b != 0) {
            if (b > 0 && a != 0) cout << " + ";
            cout << b;
        }
        if (a == 0 && b == 0) cout << "0";
        cout << endl;
    }
};

static class Kub : public Function {

private:
    double a, b, c;

public:
    Kub(double a_val = 1.0, double b_val = 0.0, double c_val = 0.0)
        : a(a_val), b(b_val), c(c_val) {}

    double calculate(double x) const override {
        return a * x * x + b * x + c;
    }

    void printInfo() const override {
        cout << "Квадратичная функция: y = ";
        bool has_terms = false;

        if (a != 0) {
            if (a != 1) cout << a;
            cout << "x^2";
            has_terms = true;
        }

        if (b != 0) {
            if (has_terms && b > 0) cout << " + ";
            if (b != 1) cout << b;
            cout << "x";
            has_terms = true;
        }

        if (c != 0) {
            if (has_terms && c > 0) cout << " + ";
            cout << c;
            has_terms = true;
        }

        if (!has_terms) cout << "0";
        cout << endl;
    }
};

static class Hyperbola : public Function {

private:
    double a;

public:
    Hyperbola(double a_val = 1.0) : a(a_val) {}

    double calculate(double x) const override {
        if (x == 0) {
            throw invalid_argument("Ошибка: деление на ноль");
        }
        return a / x;
    }

    void printInfo() const override {
        cout << "Гипербола: y = ";
        if (a != 1) cout << a;
        cout << "/x" << endl;
    }
};

void task_403() {
    SetConsoleOutputCP(1251);

    double x_point;
    cout << "Введите x: ";
    cin >> x_point;

    vector<unique_ptr<Function>> functions;
    functions.push_back(make_unique<Line>(2, 1));
    functions.push_back(make_unique<Line>(0.5, -2));
    functions.push_back(make_unique<Kub>(1, -3, 2));
    functions.push_back(make_unique<Kub>(2, 0, -1));
    functions.push_back(make_unique<Hyperbola>(4));
    functions.push_back(make_unique<Hyperbola>(9));
    functions.push_back(make_unique<Line>(0, 5));
    functions.push_back(make_unique<Kub>(0, 1, 0));

    for (size_t i = 0; i < functions.size(); i++) {
        cout << "\nФункция " << i + 1 << ":" << endl;
        functions[i]->printInfo();

        try {
            double result = functions[i]->calculate(x_point);
            cout << "Значение в точке x = " << x_point << ": y = " << result << endl;
        }
        catch (const invalid_argument& e) {
            cout << "Ошибка вычисления: " << e.what() << endl;
        }
    }
}
