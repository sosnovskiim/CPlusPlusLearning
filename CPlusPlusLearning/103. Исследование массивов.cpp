#include "tasks_1.h"
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <windows.h>

template<typename T>
void print_1d_array(T* a, size_t size) {
    for (int i = 0; i < size; i++) {
        std::cout << a[i] << " ";
    }
    std::cout << std::endl;
}

template<typename T>
void print_1d_array_ptrs(T* a, size_t size) {
    for (int i = 0; i < size; i++) {
        std::cout << "a[" + std::to_string(i) + "]  " << a + i << "  " << a[i] << std::endl;
    }
}

template<size_t rows, size_t cols>
void print_static_2d_array(int (&a)[rows][cols]) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            std::cout << a[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

template<size_t rows, size_t cols>
void print_static_2d_array_ptrs(int(&a)[rows][cols]) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            std::cout << "a[" << i << "][" << j << "]  " << &a[i][j] << "  " << a[i][j] << std::endl;
        }
    }
}

template<typename T>
void print_dynamic_2d_array(T** a, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            std::cout << a[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

template<typename T>
void print_dynamic_2d_array_ptrs(T** a, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            std::cout << "a[" << i << "][" << j << "]  " << &a[i][j] << "  " << a[i][j] << std::endl;
        }
    }
}

void task_103() {
    SetConsoleOutputCP(1251);


    std::cout << "1. Одномерный статический массив" << std::endl;

    int static_1d_uninit[5];
    std::cout << "\nНеинициализированный массив:" << std::endl;
    print_1d_array(static_1d_uninit, 5);

    int static_1d_init[5] = { 1, 2, 3, 4, 5 };
    std::cout << "\nИнициализированный массив:" << std::endl;
    print_1d_array(static_1d_init, 5);

    std::ifstream static_input_1d("in_1d.txt");
    size_t size_1d;
    static_input_1d >> size_1d;
    int static_1d_from_file[5];
    for (int i = 0; i < size_1d; i++) {
        static_input_1d >> static_1d_from_file[i];
    }
    static_input_1d.close();
    std::cout << "\nМассив из файла:" << std::endl;
    print_1d_array(static_1d_from_file, size_1d);

    std::cout << "\nАдреса элементов массива:" << std::endl;
    print_1d_array_ptrs(static_1d_from_file, size_1d);

    std::cout << "\nЭлемент на позиции [0]: " << static_1d_from_file[0] << std::endl;

    int static_1d_min_idx = 0;
    for (int i = 1; i < size_1d; i++) {
        if (abs(static_1d_from_file[i]) < abs(static_1d_from_file[static_1d_min_idx])) {
            static_1d_min_idx = i;
        }
    }
    std::cout << "\nПозиция минимального по модулю элемента: [" << static_1d_min_idx << "]" << std::endl;

    std::cout << "\nОбмен местами первого и последнего элементов:" << std::endl;
    print_1d_array(static_1d_from_file, size_1d);
    std::swap(static_1d_from_file[0], static_1d_from_file[size_1d - 1]);
    print_1d_array(static_1d_from_file, size_1d);

    std::cout << "\nПамять автоматически освобождается при выходе из области видимости." << std::endl;


    std::cout << "\n\n2. Одномерный динамический массив" << std::endl;

    int* dynamic_1d_uninit = new int[size_1d];
    std::cout << "\nНеинициализированный массив:" << std::endl;
    print_1d_array(dynamic_1d_uninit, size_1d);

    int* dynamic_1d_init = new int[size_1d] { 1, 2, 3, 4, 5 };
    std::cout << "\nИнициализированный массив:" << std::endl;
    print_1d_array(dynamic_1d_init, size_1d);

    std::ifstream dynamic_input_1d("in_1d.txt");
    dynamic_input_1d >> size_1d;
    int* dynamic_1d_from_file = new int[size_1d];
    for (int i = 0; i < size_1d; i++) {
        dynamic_input_1d >> dynamic_1d_from_file[i];
    }
    dynamic_input_1d.close();
    std::cout << "\nМассив из файла:" << std::endl;
    print_1d_array(dynamic_1d_from_file, size_1d);

    std::cout << "\nАдреса элементов массива:" << std::endl;
    print_1d_array_ptrs(dynamic_1d_from_file, size_1d);

    std::cout << "\nЭлемент на позиции [0]: " << dynamic_1d_from_file[0] << std::endl;

    int dynamic_1d_min_idx = 0;
    for (int i = 1; i < size_1d; i++) {
        if (abs(dynamic_1d_from_file[i]) < abs(dynamic_1d_from_file[dynamic_1d_min_idx])) {
            dynamic_1d_min_idx = i;
        }
    }
    std::cout << "\nПозиция минимального по модулю элемента: [" << dynamic_1d_min_idx << "]" << std::endl;

    std::cout << "\nОбмен местами первого и последнего элементов:" << std::endl;
    print_1d_array(dynamic_1d_from_file, size_1d);
    std::swap(dynamic_1d_from_file[0], dynamic_1d_from_file[size_1d - 1]);
    print_1d_array(dynamic_1d_from_file, size_1d);

    delete[] dynamic_1d_uninit;
    delete[] dynamic_1d_init;
    delete[] dynamic_1d_from_file;
    std::cout << "\nПамять освобождена с помощью delete[]." << std::endl;


    std::cout << "\n\n3. Двумерный массив как единый блок памяти" << std::endl;

    int rows = 2, cols = 3;
    int contiguous_size = rows * cols;
    int* contiguous_2d_uninit = new int[contiguous_size];
    std::cout << "\nНеинициализированный массив:" << std::endl;
    print_1d_array(contiguous_2d_uninit, contiguous_size);

    int* contiguous_2d_init = new int[contiguous_size] { 1, 2, 3, 4, 5, 6 };
    std::cout << "\nИнициализированный массив:" << std::endl;
    print_1d_array(contiguous_2d_init, contiguous_size);

    std::ifstream contiguous_input_2d("in_2d.txt");
    contiguous_input_2d >> rows >> cols;
    int* contiguous_2d_from_file = new int[contiguous_size];
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            contiguous_input_2d >> contiguous_2d_from_file[i * cols + j];
        }
    }
    contiguous_input_2d.close();
    std::cout << "\nМассив из файла:" << std::endl;
    print_1d_array(contiguous_2d_from_file, contiguous_size);

    std::cout << "\nАдреса элементов массива:" << std::endl;
    print_1d_array_ptrs(contiguous_2d_from_file, contiguous_size);

    std::cout << "\nЭлемент на позиции [0][0]: " << contiguous_2d_from_file[0] << std::endl;

    int contiguous_2d_min_row_idx = 0, contiguous_2d_min_col_idx = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            int cur_idx = contiguous_2d_min_row_idx * cols + contiguous_2d_min_col_idx;
            if (abs(contiguous_2d_from_file[i * cols + j]) < abs(contiguous_2d_from_file[cur_idx])) {
                contiguous_2d_min_row_idx = i;
                contiguous_2d_min_col_idx = j;
            }
        }
    }
    std::cout << "\nПозиция минимального по модулю элемента: [";
    std::cout << contiguous_2d_min_row_idx << "][" << contiguous_2d_min_col_idx << "]" << std::endl;

    std::cout << "\nОбмен местами первой и последней строк:" << std::endl;
    print_1d_array(contiguous_2d_from_file, contiguous_size);
    for (int j = 0; j < cols; j++) {
        std::swap(contiguous_2d_from_file[0 * cols + j], contiguous_2d_from_file[(rows - 1) * cols + j]);
    }
    print_1d_array(contiguous_2d_from_file, contiguous_size);

    delete[] contiguous_2d_uninit;
    delete[] contiguous_2d_init;
    delete[] contiguous_2d_from_file;
    std::cout << "\nПамять освобождена с помощью delete[]" << std::endl;


    std::cout << "\n\n4. Двумерный статический массив" << std::endl;

    int static_2d_uninit[2][3];
    std::cout << "\nНеинициализированный массив:" << std::endl;
    print_static_2d_array(static_2d_uninit);

    int static_2d_init[2][3] = { {1, 2, 3}, {4, 5, 6} };
    std::cout << "\nИнициализированный массив:" << std::endl;
    print_static_2d_array(static_2d_init);

    std::ifstream static_input_2d("in_2d.txt");
    static_input_2d >> rows >> cols;
    int static_2d_from_file[2][3];
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            static_input_2d >> static_2d_from_file [i][j];
        }
    }
    static_input_2d.close();
    std::cout << "\nМассив из файла:" << std::endl;
    print_static_2d_array(static_2d_from_file);

    std::cout << "\nАдреса элементов массива:" << std::endl;
    print_static_2d_array_ptrs(static_2d_from_file);

    std::cout << "\nЭлемент на позиции [0][0]: " << static_2d_from_file[0][0] << std::endl;

    int static_2d_min_row_idx = 0, static_2d_min_col_idx = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (abs(static_2d_from_file[i][j]) < abs(static_2d_from_file[static_2d_min_row_idx][static_2d_min_col_idx])) {
                static_2d_min_row_idx = i;
                static_2d_min_col_idx = j;
            }
        }
    }
    std::cout << "\nПозиция минимального по модулю элемента: [";
    std::cout << static_2d_min_row_idx << "][" << static_2d_min_col_idx << "]" << std::endl;

    std::cout << "\nОбмен местами первой и последней строк:" << std::endl;
    print_static_2d_array(static_2d_from_file);
    for (int j = 0; j < cols; j++) {
        std::swap(static_2d_from_file[0][j], static_2d_from_file[rows - 1][j]);
    }
    print_static_2d_array(static_2d_from_file);

    std::cout << "\nОбмен местами первого и последнего столбцов:" << std::endl;
    print_static_2d_array(static_2d_from_file);
    for (int i = 0; i < rows; i++) {
        std::swap(static_2d_from_file[i][0], static_2d_from_file[i][cols - 1]);
    }
    print_static_2d_array(static_2d_from_file);

    std::cout << "\nПамять автоматически освобождается при выходе из области видимости." << std::endl;


    std::cout << "\n\n5. Двумерный динамеческий массив" << std::endl;
    
    int** dynamic_2d = new int *[rows];
    for (int i = 0; i < rows; i++) {
        dynamic_2d[i] = new int[cols];
    }
    std::cout << "\nНеинициализированный массив:" << std::endl;
    print_dynamic_2d_array(dynamic_2d, rows, cols);

    int cnt = 1;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            dynamic_2d[i][j] = cnt++;
        }
    }
    std::cout << "\nИнициализированный массив:" << std::endl;
    print_dynamic_2d_array(dynamic_2d, rows, cols);

    std::ifstream dynamic_input_2d("in_2d.txt");
    dynamic_input_2d >> rows >> cols;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            dynamic_input_2d >> dynamic_2d[i][j];
        }
    }
    dynamic_input_2d.close();
    std::cout << "\nМассив из файла:" << std::endl;
    print_dynamic_2d_array(dynamic_2d, rows, cols);

    std::cout << "\nАдреса элементов массива:" << std::endl;
    print_dynamic_2d_array_ptrs(dynamic_2d, rows, cols);

    std::cout << "\nЭлемент на позиции [0][0]: " << dynamic_2d[0][0] << std::endl;

    int dynamic_2d_min_row_idx = 0, dynamic_2d_min_col_idx = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (abs(dynamic_2d[i][j]) < abs(dynamic_2d[dynamic_2d_min_row_idx][dynamic_2d_min_col_idx])) {
                dynamic_2d_min_row_idx = i;
                dynamic_2d_min_col_idx = j;
            }
        }
    }
    std::cout << "\nПозиция минимального по модулю элемента: [";
    std::cout << dynamic_2d_min_row_idx << "][" << dynamic_2d_min_col_idx << "]" << std::endl;

    std::cout << "\nОбмен местами первой и последней строк:" << std::endl;
    print_dynamic_2d_array(dynamic_2d, rows, cols);
    std::swap(dynamic_2d[0], dynamic_2d[rows - 1]);
    print_dynamic_2d_array(dynamic_2d, rows, cols);

    for (int i = 0; i < rows; i++) {
        delete[] dynamic_2d[i];
    }
    delete[] dynamic_2d;
    std::cout << "\nПамять освобождена сначала с помощью delete[] для каждой строки, а затем для массива указателей." << std::endl;
}
