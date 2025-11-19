#include "tasks_5.h"
#include <windows.h>
#include <iostream>
#include <stdexcept>
#include <memory>
#include <algorithm>
#include <string>
#include <cassert>

template<typename T>
class Vector {
private:
    T* data_ = nullptr;
    size_t size_ = 0;
    size_t capacity_ = 0;

    static constexpr size_t DEFAULT_CAPACITY = 16;
    static constexpr double EXPAND_RATIO = 1.5;

    void expand(size_t new_capacity) {
        T* new_data = static_cast<T*>(::operator new(new_capacity * sizeof(T)));

        size_t i = 0;
        try {
            for (; i < size_; i++) {
                new (new_data + i) T(std::move(data_[i]));
            }
        } catch (...) {
            for (size_t j = 0; j < i; j++) {
                new_data[j].~T();
            }
            ::operator delete(new_data);
            throw;
        }

        for (size_t i = 0; i < size_; i++) {
            data_[i].~T();
        }
        ::operator delete(data_);

        data_ = new_data;
        capacity_ = new_capacity;
    }

public:
    Vector() = default;

    explicit Vector(size_t size) : size_(size), capacity_(size) {
        if (size > 0) {
            data_ = static_cast<T*>(::operator new(size * sizeof(T)));
            size_t i = 0;
            try {
                for (; i < size; i++) {
                    new (data_ + i) T();
                }
            }
            catch (...) {
                for (size_t j = 0; j < i; j++) {
                    data_[j].~T();
                }
                ::operator delete(data_);
                throw;
            }
        }
    }

    Vector(size_t size, const T& value) : size_(size), capacity_(size) {
        if (size > 0) {
            data_ = static_cast<T*>(::operator new(size * sizeof(T)));
            size_t i = 0;
            try {
                for (; i < size; i++) {
                    new (data_ + i) T(value);
                }
            }
            catch (...) {
                for (size_t j = 0; j < i; j++) {
                    data_[j].~T();
                }
                ::operator delete(data_);
                throw;
            }
        }
    }

    Vector(const Vector& other) : size_(other.size_), capacity_(other.size_) {
        if (other.size_ > 0) {
            data_ = static_cast<T*>(::operator new(other.size_ * sizeof(T)));
            size_t i = 0;
            try {
                for (; i < other.size_; i++) {
                    new (data_ + i) T(other.data_[i]);
                }
            }
            catch (...) {
                for (size_t j = 0; j < i; j++) {
                    data_[j].~T();
                }
                ::operator delete(data_);
                throw;
            }
        }
    }

    Vector& operator=(const Vector& other) {
        if (this != &other) {
            Vector temp(other);
            swap(temp);
        }
        return *this;
    }

    ~Vector() {
        clear();
        ::operator delete(data_);
    }

    T& operator[](size_t index) {
        return data_[index];
    }

    const T& operator[](size_t index) const {
        return data_[index];
    }

    T& at(size_t index) {
        if (index >= size_) {
            throw std::out_of_range("Vector index out of range");
        }
        return data_[index];
    }

    const T& at(size_t index) const {
        if (index >= size_) {
            throw std::out_of_range("Vector index out of range");
        }
        return data_[index];
    }

    T* data() {
        return data_;
    }

    const T* data() const {
        return data_;
    }

    T& front() {
        return data_[0];
    }

    const T& front() const {
        return data_[0];
    }

    T& back() {
        return data_[size_ - 1];
    }

    const T& back() const {
        return data_[size_ - 1];
    }

    size_t size() const {
        return size_;
    }

    size_t capacity() const {
        return capacity_;
    }

    bool empty() const {
        return size_ == 0;
    }

    void push_back(const T& value) {
        if (size_ >= capacity_) {
            reserve(capacity_ == 0 ? DEFAULT_CAPACITY : static_cast<size_t>(capacity_ * EXPAND_RATIO));
        }
        new (data_ + size_) T(value);
        size_++;
    }

    void push_back(T&& value) {
        if (size_ >= capacity_) {
            reserve(capacity_ == 0 ? DEFAULT_CAPACITY : static_cast<size_t>(capacity_ * EXPAND_RATIO));
        }
        new (data_ + size_) T(std::move(value));
        size_++;
    }

    template<typename... Args>
    void emplace_back(Args&&... args) {
        if (size_ >= capacity_) {
            reserve(capacity_ == 0 ? DEFAULT_CAPACITY : static_cast<size_t>(capacity_ * EXPAND_RATIO));
        }
        new (data_ + size_) T(std::forward<Args>(args)...);
        size_++;
    }

    void pop_back() {
        if (size_ > 0) {
            data_[size_ - 1].~T();
            size_--;
        }
    }

    void clear() {
        for (size_t i = 0; i < size_; i++) {
            data_[i].~T();
        }
        size_ = 0;
    }

    void reserve(size_t new_capacity) {
        if (new_capacity > capacity_) {
            expand(new_capacity);
        }
    }

    void swap(Vector& other) noexcept {
        std::swap(data_, other.data_);
        std::swap(size_, other.size_);
        std::swap(capacity_, other.capacity_);
    }
};

template<typename T>
class SmartVector {
private:
    std::unique_ptr<T[]> data_;
    size_t size_ = 0;
    size_t capacity_ = 0;

    static constexpr size_t DEFAULT_CAPACITY = 16;
    static constexpr double EXPAND_RATIO = 1.5;

    void expand(size_t new_capacity) {
        std::unique_ptr<T[]> new_data = std::make_unique<T[]>(new_capacity);

        for (size_t i = 0; i < size_; i++) {
            new_data[i] = std::move(data_[i]);
        }

        data_ = std::move(new_data);
        capacity_ = new_capacity;
    }

public:
    SmartVector() = default;

    explicit SmartVector(size_t size) : size_(size), capacity_(size) {
        if (size > 0) {
            data_ = std::make_unique<T[]>(size);
        }
    }

    SmartVector(size_t size, const T& value) : size_(size), capacity_(size) {
        if (size > 0) {
            data_ = std::make_unique<T[]>(size);
            for (size_t i = 0; i < size; i++) {
                data_[i] = value;
            }
        }
    }

    SmartVector(const SmartVector& other) : size_(other.size_), capacity_(other.size_) {
        if (other.size_ > 0) {
            data_ = std::make_unique<T[]>(other.size_);
            for (size_t i = 0; i < other.size_; i++) {
                data_[i] = other.data_[i];
            }
        }
    }

    SmartVector& operator=(const SmartVector& other) {
        if (this != &other) {
            SmartVector temp(other);
            swap(temp);
        }
        return *this;
    }

    ~SmartVector() = default;

    T& operator[](size_t index) {
        return data_[index];
    }

    const T& operator[](size_t index) const {
        return data_[index];
    }

    T& at(size_t index) {
        if (index >= size_) {
            throw std::out_of_range("Vector index out of range");
        }
        return data_[index];
    }

    const T& at(size_t index) const {
        if (index >= size_) {
            throw std::out_of_range("Vector index out of range");
        }
        return data_[index];
    }

    T* data() {
        return data_.get();
    }

    const T* data() const {
        return data_.get();
    }

    T& front() {
        return data_[0];
    }

    const T& front() const {
        return data_[0];
    }

    T& back() {
        return data_[size_ - 1];
    }

    const T& back() const {
        return data_[size_ - 1];
    }

    size_t size() const {
        return size_;
    }

    size_t capacity() const {
        return capacity_;
    }

    bool empty() const {
        return size_ == 0;
    }

    void push_back(const T& value) {
        if (size_ >= capacity_) {
            reserve(capacity_ == 0 ? DEFAULT_CAPACITY : static_cast<size_t>(capacity_ * EXPAND_RATIO));
        }
        data_[size_] = value;
        size_++;
    }

    void push_back(T&& value) {
        if (size_ >= capacity_) {
            reserve(capacity_ == 0 ? DEFAULT_CAPACITY : static_cast<size_t>(capacity_ * EXPAND_RATIO));
        }
        data_[size_] = std::move(value);
        size_++;
    }

    template<typename... Args>
    void emplace_back(Args&&... args) {
        if (size_ >= capacity_) {
            reserve(capacity_ == 0 ? DEFAULT_CAPACITY : static_cast<size_t>(capacity_ * EXPAND_RATIO));
        }
        data_[size_] = T(std::forward<Args>(args)...);
        size_++;
    }

    void pop_back() {
        if (size_ > 0) {
            size_--;
        }
    }

    void clear() {
        size_ = 0;
    }

    void reserve(size_t new_capacity) {
        if (new_capacity > capacity_) {
            expand(new_capacity);
        }
    }

    void swap(SmartVector& other) noexcept {
        data_.swap(other.data_);
        std::swap(size_, other.size_);
        std::swap(capacity_, other.capacity_);
    }
};

void task_501() {
    SetConsoleOutputCP(1251);
    std::cout << std::boolalpha << "Тестирование класса Vector" << std::endl;

    {
        std::cout << "\nКонструкторы и базовые операции:" << std::endl;
        Vector<int> vec1;
        std::cout << vec1.size() << std::endl;  // 0
        std::cout << vec1.empty() << std::endl;  // true
        
        Vector<int> vec2(5);
        std::cout << vec2.size() << std::endl;  // 5
        std::cout << vec2.empty() << std::endl;  // false

        Vector<int> vec3(2, 10);
        std::cout << vec3.size() << std::endl;  // 2
        std::cout << vec3[0] << ' ' << vec3[1] << std::endl;  // 10 10
    }

    {
        std::cout << "\nМетоды push_back, front и back:" << std::endl;
        Vector<int> vec;

        vec.push_back(10);
        vec.push_back(20);
        vec.push_back(30);

        std::cout << vec.size() << std::endl;  // 3
        std::cout << vec[0] << ' ' << vec[1] << ' ' << vec[2] << std::endl;  // 10 20 30
        std::cout << vec.front() << ' ' << vec.back() << std::endl;  // 10 30
    }

    {
        std::cout << "\nМетод emplace_back:" << std::endl;
        Vector<std::string> vec;

        vec.emplace_back("Hello");
        vec.emplace_back("World");
        vec.emplace_back(5, 'A');

        std::cout << vec.size() << std::endl;  // 3
        std::cout << vec[0] << ' ' << vec[1] << ' ' << vec[2] << std::endl;  // Hello World AAAAA
    }

    {
        std::cout << "\nКопирование и присваивание" << std::endl;
        Vector<int> vec1;

        vec1.push_back(10);
        vec1.push_back(20);
        vec1.push_back(30);

        std::cout << vec1.size() << std::endl;  // 3
        std::cout << vec1[0] << ' ' << vec1[1] << ' ' << vec1[2] << std::endl;  // 10 20 30

        Vector<int> vec2 = vec1;
        std::cout << vec2.size() << std::endl;  // 3
        std::cout << vec2[0] << ' ' << vec2[1] << ' ' << vec2[2] << std::endl;  // 10 20 30

        Vector<int> vec3;
        vec3 = vec1;
        std::cout << vec3.size() << std::endl;  // 3
        std::cout << vec3[0] << ' ' << vec3[1] << ' ' << vec3[2] << std::endl;  // 10 20 30
    }

    {
        std::cout << "\nМетоды pop_back и clear:" << std::endl;
        Vector<int> vec;

        vec.push_back(10);
        vec.push_back(20);
        vec.push_back(30);

        std::cout << vec.size() << std::endl;  // 3
        std::cout << vec[0] << ' ' << vec[1] << ' ' << vec[2] << std::endl;  // 10 20 30

        vec.pop_back();
        std::cout << vec.size() << std::endl;  // 2
        std::cout << vec.back() << std::endl;  // 20

        vec.clear();
        std::cout << vec.size() << std::endl;  // 0
        std::cout << vec.empty() << std::endl;  // true
    }

    {
        std::cout << "\nМетоды reserve, capacity и приватный expand:" << std::endl;
        Vector<int> vec;

        vec.reserve(100);
        std::cout << vec.capacity() << ' ' << vec.size() << std::endl;  // 100 0

        for (int i = 0; i < 100; i++) {
            vec.push_back(i);
        }
        std::cout << vec.capacity() << ' ' << vec.size() << std::endl;  // 100 100

        for (int i = 100; i < 125; i++) {
            vec.push_back(i);
        }
        std::cout << vec.capacity() << ' ' << vec.size() << std::endl;  // 150 125
    }

    {
        std::cout << "\nИсключения:" << std::endl;
        Vector<int> vec;

        vec.push_back(10);
        vec.push_back(20);
        vec.push_back(30);

        std::cout << vec.size() << std::endl;  // 3
        std::cout << vec[0] << ' ' << vec[1] << ' ' << vec[2] << std::endl;  // 10 20 30

        try {
            std::cout << "Try to get vec[3]" << std::endl;
            vec.at(3);
        } catch (const std::out_of_range& e) {
            std::cout << e.what() << std::endl;
        }

        std::cout << vec.size() << std::endl;  // 3
        std::cout << vec[0] << ' ' << vec[1] << ' ' << vec[2] << std::endl;  // 10 20 30
    }

    {
        std::cout << "\nМетод data:" << std::endl;
        Vector<int> vec;

        vec.push_back(10);
        vec.push_back(20);
        vec.push_back(30);

        int* data = vec.data();
        std::cout << data[0] << ' ' << data[1] << ' ' << data[2] << std::endl;  // 10 20 30

        data[0] = 100;
        std::cout << vec[0] << std::endl;  // 100
    }

    std::cout << "\n\nТестирование класса SmartVector" << std::endl;

    {
        std::cout << "\nКонструкторы и базовые операции:" << std::endl;
        SmartVector<int> vec1;
        std::cout << vec1.size() << std::endl;  // 0
        std::cout << vec1.empty() << std::endl;  // true

        SmartVector<int> vec2(5);
        std::cout << vec2.size() << std::endl;  // 5
        std::cout << vec2.empty() << std::endl;  // false

        SmartVector<int> vec3(2, 10);
        std::cout << vec3.size() << std::endl;  // 2
        std::cout << vec3[0] << ' ' << vec3[1] << std::endl;  // 10 10
    }

    {
        std::cout << "\nМетоды push_back, front и back:" << std::endl;
        SmartVector<int> vec;

        vec.push_back(10);
        vec.push_back(20);
        vec.push_back(30);

        std::cout << vec.size() << std::endl;  // 3
        std::cout << vec[0] << ' ' << vec[1] << ' ' << vec[2] << std::endl;  // 10 20 30
        std::cout << vec.front() << ' ' << vec.back() << std::endl;  // 10 30
    }

    {
        std::cout << "\nМетод emplace_back:" << std::endl;
        SmartVector<std::string> vec;

        vec.emplace_back("Hello");
        vec.emplace_back("World");
        vec.emplace_back(5, 'A');

        std::cout << vec.size() << std::endl;  // 3
        std::cout << vec[0] << ' ' << vec[1] << ' ' << vec[2] << std::endl;  // Hello World AAAAA
    }

    {
        std::cout << "\nКопирование и присваивание" << std::endl;
        SmartVector<int> vec1;

        vec1.push_back(10);
        vec1.push_back(20);
        vec1.push_back(30);

        std::cout << vec1.size() << std::endl;  // 3
        std::cout << vec1[0] << ' ' << vec1[1] << ' ' << vec1[2] << std::endl;  // 10 20 30

        SmartVector<int> vec2 = vec1;
        std::cout << vec2.size() << std::endl;  // 3
        std::cout << vec2[0] << ' ' << vec2[1] << ' ' << vec2[2] << std::endl;  // 10 20 30

        SmartVector<int> vec3;
        vec3 = vec1;
        std::cout << vec3.size() << std::endl;  // 3
        std::cout << vec3[0] << ' ' << vec3[1] << ' ' << vec3[2] << std::endl;  // 10 20 30
    }

    {
        std::cout << "\nМетоды pop_back и clear:" << std::endl;
        SmartVector<int> vec;

        vec.push_back(10);
        vec.push_back(20);
        vec.push_back(30);

        std::cout << vec.size() << std::endl;  // 3
        std::cout << vec[0] << ' ' << vec[1] << ' ' << vec[2] << std::endl;  // 10 20 30

        vec.pop_back();
        std::cout << vec.size() << std::endl;  // 2
        std::cout << vec.back() << std::endl;  // 20

        vec.clear();
        std::cout << vec.size() << std::endl;  // 0
        std::cout << vec.empty() << std::endl;  // true
    }

    {
        std::cout << "\nМетоды reserve, capacity и приватный expand:" << std::endl;
        SmartVector<int> vec;

        vec.reserve(100);
        std::cout << vec.capacity() << ' ' << vec.size() << std::endl;  // 100 0

        for (int i = 0; i < 100; i++) {
            vec.push_back(i);
        }
        std::cout << vec.capacity() << ' ' << vec.size() << std::endl;  // 100 100

        for (int i = 100; i < 125; i++) {
            vec.push_back(i);
        }
        std::cout << vec.capacity() << ' ' << vec.size() << std::endl;  // 150 125
    }

    {
        std::cout << "\nИсключения:" << std::endl;
        SmartVector<int> vec;

        vec.push_back(10);
        vec.push_back(20);
        vec.push_back(30);

        std::cout << vec.size() << std::endl;  // 3
        std::cout << vec[0] << ' ' << vec[1] << ' ' << vec[2] << std::endl;  // 10 20 30

        try {
            std::cout << "Try to get vec[3]" << std::endl;
            vec.at(3);
        }
        catch (const std::out_of_range& e) {
            std::cout << e.what() << std::endl;
        }

        std::cout << vec.size() << std::endl;  // 3
        std::cout << vec[0] << ' ' << vec[1] << ' ' << vec[2] << std::endl;  // 10 20 30
    }

    {
        std::cout << "\nМетод data:" << std::endl;
        SmartVector<int> vec;

        vec.push_back(10);
        vec.push_back(20);
        vec.push_back(30);

        int* data = vec.data();
        std::cout << data[0] << ' ' << data[1] << ' ' << data[2] << std::endl;  // 10 20 30

        data[0] = 100;
        std::cout << vec[0] << std::endl;  // 100
    }
}
