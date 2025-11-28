#include "tasks_5.h"
#include <iostream>
#include <list>
#include <vector>
#include <stdexcept>
#include <iterator>
#include <cstdlib>

template <typename T>
class AdvancedVector {
private:
    std::vector<T> data;

public:
    AdvancedVector() = default;

    AdvancedVector(const AdvancedVector&) = default;

    template <typename InputIterator>
    AdvancedVector(InputIterator first, InputIterator last) : data(first, last) {}

    AdvancedVector& operator=(const AdvancedVector&) = default;

    bool operator==(const AdvancedVector& other) const {
        return data == other.data;
    }

    bool operator!=(const AdvancedVector& other) const {
        return data != other.data;
    }

    bool empty() const {
        return data.empty();
    }

    size_t size() const {
        return data.size();
    }

    void pop_back() {
        data.pop_back();
    }

    void push_back(const T& value) {
        data.push_back(value);
    }

    T& operator[](int index) {
        return at_impl(index);
    }

    const T& operator[](int index) const {
        return at_impl(index);
    }

private:
    T& at_impl(int index) const {
        size_t pos = convert_index(index);
        if (pos >= data.size()) {
            throw std::out_of_range("Index out of range");
        }
        return const_cast<T&>(data[pos]);
    }

    size_t convert_index(int index) const {
        if (index >= 0) {
            return static_cast<size_t>(index);
        }
        else {
            long long positive_index = static_cast<long long>(data.size()) + index;
            if (positive_index < 0) {
                throw std::out_of_range("Index out of range");
            }
            return static_cast<size_t>(positive_index);
        }
    }
};

void task_504() {
    AdvancedVector<int> vec1;

    std::list<int> lst = { 10, 20, 30, 40, 50 };
    AdvancedVector<int> vec2(lst.begin(), lst.end());

    vec2.push_back(60);

    std::cout << vec2[0] << std::endl;
    std::cout << vec2[2] << std::endl;

    std::cout << vec2[-1] << std::endl;
    std::cout << vec2[-2] << std::endl;

    try {
        std::cout << vec2[10] << std::endl;
    }
    catch (const std::out_of_range& e) {
        std::cout << "Caught: " << e.what() << std::endl;
    }

    try {
        std::cout << vec2[-10] << std::endl;
    }
    catch (const std::out_of_range& e) {
        std::cout << "Caught: " << e.what() << std::endl;
    }
}
