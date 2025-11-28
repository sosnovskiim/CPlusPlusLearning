#include "tasks_5.h"
#include <iostream>
#include <deque>
#include <vector>

template <typename T, typename Container = std::deque<T>>
class Queue {
private:
    Container container;

public:
    Queue() = default;

    const T& front() const {
        return container.front();
    }

    T& front() {
        return container.front();
    }

    void pop() {
        container.pop_front();
    }

    void push(const T& value) {
        container.push_back(value);
    }

    void push(T&& value) {
        container.push_back(std::move(value));
    }

    size_t size() const {
        return container.size();
    }

    bool empty() const {
        return container.empty();
    }

    bool operator==(const Queue& other) const {
        return container == other.container;
    }

    bool operator!=(const Queue& other) const {
        return container != other.container;
    }
};

void task_501() {
    Queue<int> q1;
    q1.push(10);
    q1.push(20);
    q1.push(30);

    std::cout << q1.front() << std::endl;
    q1.pop();
    std::cout << q1.front() << std::endl;
    std::cout << q1.size() << std::endl;

    Queue<int, std::vector<int>> q2;
    q2.push(10);
    q2.push(20);

    q2.front() = 30;
    std::cout << q2.front() << std::endl;
}
