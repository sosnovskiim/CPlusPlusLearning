#include "tasks_2.h"
#include <iostream>
#include <fstream>
#include <random>
#include <iomanip>
#include <memory>
#include <vector>
#include <functional>
#include <type_traits>
#include <windows.h>

template<typename T>
using TableRow = std::unique_ptr<T[]>;

template<typename T>
using TablePtr = std::unique_ptr<TableRow<T>[], std::function<void(TableRow<T>*)>>;

template<typename T>
T** create_table(int rows, int cols) {
    T** table = new T * [rows];
    for (int i = 0; i < rows; i++) {
        table[i] = new T[cols];
    }
    return table;
}

template<typename T>
TablePtr<T> create_table_smart(int rows, int cols) {
    TableRow<T>* raw_table = new TableRow<T>[rows];

    for (int i = 0; i < rows; i++) {
        raw_table[i] = TableRow<T>(new T[cols]);
    }

    return TablePtr<T>(
        raw_table,
        [rows](TableRow<T>* ptr) {
            for (int i = 0; i < rows; i++) {
                ptr[i].reset();
            }
            delete[] ptr;
        }
    );
}

template<typename T>
T** create_table(int size) {
    return create_table<T>(size, size);
}

template<typename T>
TablePtr<T> create_table_smart(int size) {
    return create_table_smart<T>(size, size);
}

template<typename T>
void fill_with_zeros(T** table, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            table[i][j] = T(0);
        }
    }
}

template<typename T>
void fill_with_zeros(TablePtr<T>& table, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            table[i][j] = T(0);
        }
    }
}

template<typename T>
void fill_with_random(T** table, int rows, int cols, T min_val, T max_val) {
    std::random_device rd;
    std::mt19937 gen(rd());

    if constexpr (std::is_integral_v<T>) {
        std::uniform_int_distribution<T> dist(min_val, max_val);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                table[i][j] = dist(gen);
            }
        }
    }
    else {
        std::uniform_real_distribution<T> dist(min_val, max_val);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                table[i][j] = dist(gen);
            }
        }
    }
}

template<typename T>
void fill_with_random(TablePtr<T>& table, int rows, int cols, T min_val, T max_val) {
    std::random_device rd;
    std::mt19937 gen(rd());

    if constexpr (std::is_integral_v<T>) {
        std::uniform_int_distribution<T> dist(min_val, max_val);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                table[i][j] = dist(gen);
            }
        }
    }
    else {
        std::uniform_real_distribution<T> dist(min_val, max_val);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                table[i][j] = dist(gen);
            }
        }
    }
}

template<typename T>
void fill_from_console(T** table, int rows, int cols) {
    std::cout << "Введите " << rows << " строк по " << cols << " элементов:" << std::endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            std::cin >> table[i][j];
        }
    }
}

template<typename T>
void fill_from_console(TablePtr<T>& table, int rows, int cols) {
    std::cout << "Введите " << rows << " строк по " << cols << " элементов:" << std::endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            std::cin >> table[i][j];
        }
    }
}

template<typename T>
bool fill_from_file(T** table, int rows, int cols, const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        return false;
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (!(file >> table[i][j])) {
                return false;
            }
        }
    }
    return true;
}

template<typename T>
bool fill_from_file(TablePtr<T>& table, int rows, int cols, const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        return false;
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (!(file >> table[i][j])) {
                return false;
            }
        }
    }
    return true;
}

template<typename T>
void print_to_console(T** table, int rows, int cols, int width = 4) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            std::cout << std::setw(width) << table[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

template<typename T>
void print_to_console(TablePtr<T>& table, int rows, int cols, int width = 4) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            std::cout << std::setw(width) << table[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

template<typename T>
bool print_to_file(T** table, int rows, int cols, const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        return false;
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            file << table[i][j] << " ";
        }
        file << std::endl;
    }
    return true;
}

template<typename T>
bool print_to_file(TablePtr<T>& table, int rows, int cols, const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        return false;
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            file << table[i][j] << " ";
        }
        file << std::endl;
    }
    return true;
}

template<typename T>
void delete_table(T** table, int rows) {
    for (int i = 0; i < rows; i++) {
        delete[] table[i];
    }
    delete[] table;
}

template<typename T>
T product_elements_is_greater_than_average_by_two_times(T** table, int rows, int cols) {
    T sum = T(0);
    int cnt = rows * cols;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            sum += table[i][j];
        }
    }

    T avg = sum / cnt;
    T pr = T(1);
    bool is_exists = false;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            T a = table[i][j];
            if (a > 2 * avg || a < avg / 2) {
                pr *= a;
                is_exists = true;
            }
        }
    }

    return is_exists ? pr : T(0);
}

template<typename T>
T product_elements_is_greater_than_average_by_two_times(TablePtr<T>& table, int rows, int cols) {
    T sum = T(0);
    int cnt = rows * cols;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            sum += table[i][j];
        }
    }

    T avg = sum / cnt;
    T pr = T(1);
    bool is_exists = false;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            T a = table[i][j];
            if (a > 2 * avg || a < avg / 2) {
                pr *= a;
                is_exists = true;
            }
        }
    }

    return is_exists ? pr : T(0);
}

void task_212() {
    SetConsoleOutputCP(1251);

    const std::string filename = "test_212.txt";

    int rows = 3, cols = 5;
    int** table = create_table<int>(rows, cols);

    //fill_with_random(table, rows, cols, 1, 10);
    //print_to_file(table, rows, cols, filename);

    fill_from_file(table, rows, cols, filename);

    std::cout << "Таблица с обычными указателями:" << std::endl;
    print_to_console(table, rows, cols);

    int result = product_elements_is_greater_than_average_by_two_times(table, rows, cols);
    std::cout << "\nПроизведение: " << result << std::endl;

    delete_table(table, rows);

    auto table_smart = create_table_smart<double>(rows, cols);
    fill_with_random(table_smart, rows, cols, 1.0, 10.0);

    std::cout << "\n\nТаблица с умными указателями:" << std::endl;
    print_to_console(table_smart, rows, cols);

    double result_smart = product_elements_is_greater_than_average_by_two_times(table_smart, rows, cols);
    std::cout << "\nПроизведение: " << result_smart << std::endl;
}
