#include "tasks_5.h"
#include <windows.h>
#include <iostream>
#include <stdexcept>
#include <utility>

template <typename T>
struct Node {
    T data;
    Node* next;

    Node(const T& value) : data(value), next(nullptr) {}
    Node(T&& value) : data(std::move(value)), next(nullptr) {}
};

template <typename T>
class List {
private:
    Node<T>* head;
    Node<T>* tail;
    size_t size_;

public:
    List() : head(nullptr), tail(nullptr), size_(0) {}

    List(const List&) = delete;
    List& operator=(const List&) = delete;

    List(List&& other) noexcept
        : head(other.head), tail(other.tail), size_(other.size_) {
        other.head = other.tail = nullptr;
        other.size_ = 0;
    }

    List& operator=(List&& other) noexcept {
        if (this != &other) {
            clear();
            head = other.head;
            tail = other.tail;
            size_ = other.size_;
            other.head = other.tail = nullptr;
            other.size_ = 0;
        }
        return *this;
    }

    ~List() {
        clear();
    }

    void clear() {
        while (head) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
        }
        tail = nullptr;
        size_ = 0;
    }

    void push_back(const T& value) {
        Node<T>* newNode = new Node<T>(value);
        if (!tail) {
            head = tail = newNode;
        }
        else {
            tail->next = newNode;
            tail = newNode;
        }
        size_++;
    }

    void push_back(T&& value) {
        Node<T>* newNode = new Node<T>(std::move(value));
        if (!tail) {
            head = tail = newNode;
        }
        else {
            tail->next = newNode;
            tail = newNode;
        }
        size_++;
    }

    void push_front(const T& value) {
        Node<T>* newNode = new Node<T>(value);
        if (!head) {
            head = tail = newNode;
        }
        else {
            newNode->next = head;
            head = newNode;
        }
        size_++;
    }

    void push_front(T&& value) {
        Node<T>* newNode = new Node<T>(std::move(value));
        if (!head) {
            head = tail = newNode;
        }
        else {
            newNode->next = head;
            head = newNode;
        }
        size_++;
    }

    void pop_front() {
        if (!head) throw std::runtime_error("List is empty");

        Node<T>* temp = head;
        head = head->next;
        if (!head) tail = nullptr;
        delete temp;
        size_--;
    }

    T& front() {
        if (!head) throw std::runtime_error("List is empty");
        return head->data;
    }

    const T& front() const {
        if (!head) throw std::runtime_error("List is empty");
        return head->data;
    }

    T& back() {
        if (!tail) throw std::runtime_error("List is empty");
        return tail->data;
    }

    const T& back() const {
        if (!tail) throw std::runtime_error("List is empty");
        return tail->data;
    }

    size_t size() const { return size_; }
    bool empty() const { return size_ == 0; }

    void rotate(size_t k) {
        if (size_ <= 1 || k % size_ == 0) return;

        k = k % size_;

        Node<T>* new_tail = head;
        for (size_t i = 0; i < size_ - k - 1; ++i) {
            new_tail = new_tail->next;
        }

        Node<T>* new_head = new_tail->next;
        new_tail->next = nullptr;
        tail->next = head;
        head = new_head;
        tail = new_tail;
    }

    void print() const {
        Node<T>* current = head;
        while (current) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }
};

template <typename T>
class Queue {
private:
    List<T> list;

public:
    Queue() = default;

    Queue(const Queue&) = delete;
    Queue& operator=(const Queue&) = delete;

    Queue(Queue&& other) noexcept = default;
    Queue& operator=(Queue&& other) noexcept = default;

    void push(const T& value) {
        list.push_back(value);
    }

    void push(T&& value) {
        list.push_back(std::move(value));
    }

    void pop() {
        list.pop_front();
    }

    T& front() {
        return list.front();
    }

    const T& front() const {
        return list.front();
    }

    T& back() {
        return list.back();
    }

    const T& back() const {
        return list.back();
    }

    size_t size() const {
        return list.size();
    }

    bool empty() const {
        return list.empty();
    }

    void push_front(const T&) = delete;
    void push_front(T&&) = delete;
    void pop_back() = delete;

    void rotate(size_t k) {
        list.rotate(k);
    }

    void print() const {
        list.print();
    }
};

template <typename T>
void rotate(Queue<T>& queue, size_t k) {
    if (queue.empty() || k % queue.size() == 0) return;

    k = k % queue.size();

    for (size_t i = 0; i < queue.size() - k; ++i) {
        T elem = std::move(queue.front());
        queue.pop();
        queue.push(std::move(elem));
    }
}

void task_508() {
    SetConsoleOutputCP(1251);
    int k = 2;

    {
        std::cout << "Тестирование класса List:" << std::endl;
        List<int> list;
        for (int i = 10; i <= 50; i += 10) {
            list.push_back(i);
        }

        std::cout << "\nИсходный список: ";
        list.print();

        list.rotate(k);
        std::cout << "\nСписок после сдвига элементов: ";
        list.print();
    }

    {
        std::cout << "\n\nТестирование класса Queue с внешней функцией:" << std::endl;
        Queue<int> queue;
        for (int i = 10; i <= 50; i += 10) {
            queue.push(i);
        }

        std::cout << "\nИсходная очередь: ";
        queue.print();

        rotate(queue, k);
        std::cout << "\nОчередь после сдвига элементов: ";
        queue.print();
    }

    {
        std::cout << "\n\nТестирование класса Queue с методом:" << std::endl;
        Queue<int> queue;
        for (int i = 10; i <= 50; i += 10) {
            queue.push(i);
        }

        std::cout << "\nИсходная очередь: ";
        queue.print();

        queue.rotate(k);
        std::cout << "\nОчередь после сдвига элементов: ";
        queue.print();
    }
}
