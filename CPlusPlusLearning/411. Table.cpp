#include "tasks_4.h"
#include <iostream>
#include <vector>
#include <utility>

template<typename T>
class Table {
private:
    std::vector<std::vector<T>> data;
    size_t rows;
    size_t cols;

public:
    Table(size_t num_rows, size_t num_cols) : rows(num_rows), cols(num_cols) {
        data.resize(rows);
        for (size_t i = 0; i < rows; ++i) {
            data[i].resize(cols);
        }
    }

    std::vector<T>& operator[](size_t index) {
        return data[index];
    }

    const std::vector<T>& operator[](size_t index) const {
        return data[index];
    }

    void resize(size_t new_rows, size_t new_cols) {
        data.resize(new_rows);
        for (size_t i = 0; i < new_rows; ++i) {
            data[i].resize(new_cols);
        }
        rows = new_rows;
        cols = new_cols;
    }

    std::pair<size_t, size_t> size() const {
        return { rows, cols };
    }
};

void task_411() {
    Table<int> table(3, 4);

    for (size_t i = 0; i < table.size().first; ++i) {
        for (size_t j = 0; j < table.size().second; ++j) {
            table[i][j] = i * 10 + j;
        }
    }

    for (size_t i = 0; i < table.size().first; ++i) {
        for (size_t j = 0; j < table.size().second; ++j) {
            std::cout << table[i][j] << " ";
        }
        std::cout << "\n";
    }

    table.resize(5, 6);
    std::cout << "New size: " << table.size().first << " x " << table.size().second << "\n";
}
