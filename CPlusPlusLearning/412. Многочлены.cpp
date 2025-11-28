#include "tasks_4.h"
#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator>

template<typename T>
class Polynomial {
private:
    std::vector<T> coeffs;

    void normalize() {
        while (!coeffs.empty() && coeffs.back() == T(0)) {
            coeffs.pop_back();
        }
    }

public:
    Polynomial(const std::vector<T>& coefficients) : coeffs(coefficients) {
        normalize();
    }

    Polynomial(const T& scalar = T(0)) {
        if (scalar != T(0)) {
            coeffs.push_back(scalar);
        }
    }

    template<typename Iter>
    Polynomial(Iter first, Iter last) : coeffs(first, last) {
        normalize();
    }

    int Degree() const {
        if (coeffs.empty()) {
            return -1;
        }
        return static_cast<int>(coeffs.size()) - 1;
    }

    T operator[](size_t power) const {
        if (power < coeffs.size()) {
            return coeffs[power];
        }
        return T(0);
    }

    T operator()(const T& x) const {
        if (coeffs.empty()) {
            return T(0);
        }

        T result = T(0);
        T x_power = T(1);

        for (size_t i = 0; i < coeffs.size(); ++i) {
            result += coeffs[i] * x_power;
            x_power *= x;
        }

        return result;
    }

    auto begin() const { return coeffs.begin(); }
    auto end() const { return coeffs.end(); }

    bool operator==(const Polynomial& other) const {
        return coeffs == other.coeffs;
    }

    bool operator!=(const Polynomial& other) const {
        return !(*this == other);
    }

    bool operator==(const T& scalar) const {
        return *this == Polynomial(scalar);
    }

    bool operator!=(const T& scalar) const {
        return !(*this == scalar);
    }

    Polynomial& operator+=(const Polynomial& other) {
        if (other.coeffs.size() > coeffs.size()) {
            coeffs.resize(other.coeffs.size(), T(0));
        }

        for (size_t i = 0; i < other.coeffs.size(); ++i) {
            coeffs[i] += other.coeffs[i];
        }

        normalize();
        return *this;
    }

    Polynomial& operator-=(const Polynomial& other) {
        if (other.coeffs.size() > coeffs.size()) {
            coeffs.resize(other.coeffs.size(), T(0));
        }

        for (size_t i = 0; i < other.coeffs.size(); ++i) {
            coeffs[i] -= other.coeffs[i];
        }

        normalize();
        return *this;
    }

    Polynomial& operator*=(const Polynomial& other) {
        if (coeffs.empty() || other.coeffs.empty()) {
            coeffs.clear();
            return *this;
        }

        std::vector<T> result(coeffs.size() + other.coeffs.size() - 1, T(0));

        for (size_t i = 0; i < coeffs.size(); ++i) {
            for (size_t j = 0; j < other.coeffs.size(); ++j) {
                result[i + j] += coeffs[i] * other.coeffs[j];
            }
        }

        coeffs = result;
        normalize();
        return *this;
    }

    Polynomial& operator+=(const T& scalar) {
        return *this += Polynomial(scalar);
    }

    Polynomial& operator-=(const T& scalar) {
        return *this -= Polynomial(scalar);
    }

    Polynomial& operator*=(const T& scalar) {
        if (scalar == T(0)) {
            coeffs.clear();
        }
        else {
            for (auto& coeff : coeffs) {
                coeff *= scalar;
            }
        }
        return *this;
    }

    Polynomial operator+() const {
        return *this;
    }

    Polynomial operator-() const {
        Polynomial result = *this;
        for (auto& coeff : result.coeffs) {
            coeff = -coeff;
        }
        return result;
    }

    friend Polynomial operator+(Polynomial lhs, const Polynomial& rhs) {
        return lhs += rhs;
    }

    friend Polynomial operator-(Polynomial lhs, const Polynomial& rhs) {
        return lhs -= rhs;
    }

    friend Polynomial operator*(Polynomial lhs, const Polynomial& rhs) {
        return lhs *= rhs;
    }

    friend Polynomial operator+(Polynomial poly, const T& scalar) {
        return poly += scalar;
    }

    friend Polynomial operator-(Polynomial poly, const T& scalar) {
        return poly -= scalar;
    }

    friend Polynomial operator*(Polynomial poly, const T& scalar) {
        return poly *= scalar;
    }

    friend Polynomial operator+(const T& scalar, const Polynomial& poly) {
        return poly + scalar;
    }

    friend Polynomial operator-(const T& scalar, const Polynomial& poly) {
        return Polynomial(scalar) - poly;
    }

    friend Polynomial operator*(const T& scalar, const Polynomial& poly) {
        return poly * scalar;
    }

    friend bool operator==(const T& scalar, const Polynomial& poly) {
        return poly == scalar;
    }

    friend bool operator!=(const T& scalar, const Polynomial& poly) {
        return poly != scalar;
    }

    friend std::ostream& operator<<(std::ostream& out, const Polynomial& poly) {
        if (poly.Degree() == -1) {
            return out;
        }

        auto degree = poly.Degree();
        for (int i = degree; i >= 0; --i) {
            out << poly[i];
            if (i > 0) {
                out << " ";
            }
        }

        return out;
    }
};

void task_412() {
    std::vector<int> coeffs1 = { 1, 2, 3 };
    Polynomial<int> p1(coeffs1);
    Polynomial<int> p2(5);
    std::vector<int> coeffs3 = { 2, 0, 1, 4 };
    Polynomial<int> p3(coeffs3.begin(), coeffs3.end());

    std::cout << "p1 = " << p1 << std::endl;
    std::cout << "p2 = " << p2 << std::endl;
    std::cout << "p3 = " << p3 << std::endl;

    std::cout << "Pow p1: " << p1.Degree() << std::endl;
    std::cout << "Pow p2: " << p2.Degree() << std::endl;

    std::cout << "p1[0] = " << p1[0] << std::endl;
    std::cout << "p1[2] = " << p1[2] << std::endl;
    std::cout << "p1[5] = " << p1[5] << std::endl;

    Polynomial<int> sum = p1 + p3;
    std::cout << "p1 + p3 = " << sum << std::endl;

    Polynomial<int> product = p1 * p2;
    std::cout << "p1 * p2 = " << product << std::endl;

    Polynomial<int> p4 = p1 + 10;
    std::cout << "p1 + 10 = " << p4 << std::endl;

    Polynomial<int> p5 = 3 * p1;
    std::cout << "3 * p1 = " << p5 << std::endl;

    std::cout << "p1(2) = " << p1(2) << std::endl;

    std::cout << "p1 == p2: " << (p1 == p2) << std::endl;
    std::cout << "p2 == 5: " << (p2 == 5) << std::endl;

    std::cout << "Coeffs p1: ";
    for (auto coeff : p1) {
        std::cout << coeff << " ";
    }
    std::cout << std::endl;
}
