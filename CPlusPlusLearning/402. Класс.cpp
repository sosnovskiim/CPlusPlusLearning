#include "tasks_4.h"
#include <iostream>
#include <vector>

#define NOMINMAX
#include <windows.h>

static class IntArray {

private:
    std::vector<std::vector<int>> intArray;
    static int instanceCount;

public:
    IntArray() {
        instanceCount++;
        std::cout << "Вызван конструктор по умолчанию. Экземпляров: " << instanceCount << std::endl;
    }

    IntArray(int rows, int cols) {
        intArray.resize(rows, std::vector<int>(cols, 0));
        instanceCount++;
        std::cout << "Вызван конструктор инициализации "
            << rows << "x" << cols << ". Экземпляров: " << instanceCount << std::endl;
    }

    ~IntArray() {
        instanceCount--;
        std::cout << "Вызван деструктор. Экземпляров: " << instanceCount << std::endl;
    }

    static int getInstanceCount() {
        return instanceCount;
    }

    void inputArray() {
        std::cout << "Введите элементы массива " << getRows() << "x" << getColumns() << ":" << std::endl;
        for (int i = 0; i < getRows(); i++) {
            for (int j = 0; j < getColumns(); j++) {
                std::cin >> intArray[i][j];
            }
        }
    }

    void printArray() const {
        std::cout << "Массив " << getRows() << "x" << getColumns() << ":" << std::endl;
        for (const auto& row : intArray) {
            for (int x : row) {
                std::cout << x << " ";
            }
            std::cout << std::endl;
        }
    }

    int sumOfColumn(int column) const {
        if (column < 0 || column >= getColumns()) {
            std::cout << "Ошибка: неверный индекс столбца!" << std::endl;
            return 0;
        }

        int sum = 0;
        for (int i = 0; i < getRows(); i++) {
            sum += intArray[i][column];
        }
        return sum;
    }

    int countZeros() const {
        int count = 0;
        for (const auto& row : intArray) {
            for (int x : row) {
                if (x == 0) {
                    count++;
                }
            }
        }
        return count;
    }

    void setMainDiagonal(int a) {
        int minSize = std::min(getRows(), getColumns());
        for (int i = 0; i < minSize; i++) {
            intArray[i][i] = a;
        }
    }

    int getRows() const { return intArray.size(); }
    int getColumns() const { return intArray.empty() ? 0 : intArray[0].size(); }

    IntArray& operator++() {
        for (auto& row : intArray) {
            for (auto& x : row) {
                x++;
            }
        }
        return *this;
    }

    IntArray operator++(int) {
        IntArray temp = *this;
        ++(*this);
        return temp;
    }

    IntArray& operator--() {
        for (auto& row : intArray) {
            for (auto& x : row) {
                x--;
            }
        }
        return *this;
    }

    IntArray operator--(int) {
        IntArray temp = *this;
        --(*this);
        return temp;
    }

    IntArray operator+(const IntArray& other) const {
        if (getRows() != other.getRows() || getColumns() != other.getColumns()) {
            std::cout << "Ошибка: размеры массивов не совпадают" << std::endl;
            return IntArray(0, 0);
        }

        IntArray result(getRows(), getColumns());
        for (int i = 0; i < getRows(); i++) {
            for (int j = 0; j < getColumns(); j++) {
                result.intArray[i][j] = intArray[i][j] + other.intArray[i][j];
            }
        }
        return result;
    }

    IntArray& operator=(const IntArray& other) {
        if (this != &other) {
            intArray = other.intArray;
        }
        return *this;
    }
};

int IntArray::instanceCount = 0;

void task_402() {
    SetConsoleOutputCP(1251);

    std::cout << "Создание v:" << std::endl;
    IntArray arr1(2, 2);
    IntArray arr2(2, 2);

    std::cout << std::endl;
    arr1.inputArray();

    std::cout << std::endl;
    arr2.inputArray();

    std::cout << "\nДемонстрация методов класса:" << std::endl;
    std::cout << "Сумма элементов 1-го столбца массива 1: " << arr1.sumOfColumn(1) << std::endl;
    std::cout << "Количество нулей в массиве 1: " << arr1.countZeros() << std::endl;

    std::cout << "\nУстановка главной диагонали:" << std::endl;
    arr1.setMainDiagonal(0);
    std::cout << "После установки главной диагонали в 0:" << std::endl;
    arr1.printArray();
    std::cout << "Количество нулей теперь: " << arr1.countZeros() << std::endl;

    std::cout << "\nОператор '++':" << std::endl;
    ++arr1;
    arr1.printArray();

    std::cout << "\nОператор '--':" << std::endl;
    --arr1;
    arr1.printArray();

    std::cout << "\nОператор '+':" << std::endl;
    IntArray arr3 = arr1 + arr2;
    arr3.printArray();
}