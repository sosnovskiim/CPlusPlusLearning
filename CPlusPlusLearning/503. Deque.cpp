#include "tasks_5.h"
#include <iostream>
#include <cstddef>
#include <vector>
#include <stdexcept>

template <typename T>
class Deque {
private:
    std::vector<T> head, tail;

public:
    bool Empty() const {
        return head.empty() && tail.empty();
    }

    size_t Size() const {
        return head.size() + tail.size();
    }

    void Clear() {
        head.clear();
        tail.clear();
    }

    const T& operator [] (size_t i) const {
        if (i < head.size()) {
            return head[head.size() - 1 - i];
        }
        else {
            return tail[i - head.size()];
        }
    }

    T& operator [] (size_t i) {
        if (i < head.size()) {
            return head[head.size() - 1 - i];
        }
        else {
            return tail[i - head.size()];
        }
    }

    const T& At(size_t i) const {
        if (i >= Size()) {
            throw std::out_of_range("Index out of range");
        }
        return (*this)[i];
    }

    T& At(size_t i) {
        if (i >= Size()) {
            throw std::out_of_range("Index out of range");
        }
        return (*this)[i];
    }

    const T& Front() const {
        if (!head.empty()) {
            return head.back();
        }
        else if (!tail.empty()) {
            return tail.front();
        }
        else {
            throw std::out_of_range("Deque is empty");
        }
    }

    T& Front() {
        if (!head.empty()) {
            return head.back();
        }
        else if (!tail.empty()) {
            return tail.front();
        }
        else {
            throw std::out_of_range("Deque is empty");
        }
    }

    const T& Back() const {
        if (!tail.empty()) {
            return tail.back();
        }
        else if (!head.empty()) {
            return head.front();
        }
        else {
            throw std::out_of_range("Deque is empty");
        }
    }

    T& Back() {
        if (!tail.empty()) {
            return tail.back();
        }
        else if (!head.empty()) {
            return head.front();
        }
        else {
            throw std::out_of_range("Deque is empty");
        }
    }

    void PushFront(const T& elem) {
        head.push_back(elem);
    }

    void PushBack(const T& elem) {
        tail.push_back(elem);
    }
};

void task_503() {
    Deque<int> d;

    d.PushFront(10);
    d.PushBack(20);
    d.PushFront(30);

    std::cout << d.Size() << std::endl;
    std::cout << d.Front() << std::endl;
    std::cout << d.Back() << std::endl;

    for (size_t i = 0; i < d.Size(); ++i) {
        std::cout << d[i] << " ";
    }
    std::cout << std::endl;
}
