#include "tasks_1.h"
#include <iostream>
#include <string>
#include <windows.h>

template<typename T>
static void print_nullptr(const std::string& ptr_name, T* ptr) {
    std::cout << ptr_name << "  " << ptr << std::endl;
}

template<typename T>
static void print_ptr(const std::string& ptr_name, T* ptr) {
    std::cout << ptr_name << "  " << ptr << "  " << *ptr << std::endl;
}

template<typename T>
static void print_ptr_with_memory(const std::string& ptr_name, T* ptr, size_t size) {
    unsigned char* bytes = reinterpret_cast<unsigned char*>(ptr);

    std::cout << ptr_name << "  " << ptr << "  " << *ptr << "  ";
    for (int i = sizeof(int) - 1; i >= 0; i--) {
        printf("%02x", bytes[i]);
    }
    std::cout << std::endl;
}

void task_101() {
    SetConsoleOutputCP(1251);


    std::cout << "1. Создание неинициализированных указателей и инициализированных nullptr:" << std::endl;

    int* uninit_int_ptr;
    double* uninit_double_ptr;

    std::cout << std::endl;
    std::cout << "uninit_int_ptr" << std::endl;
    std::cout << "uninit_double_ptr" << std::endl;
    std::cout << "Просмотр и разыменование неинициализированных указателей невозможно." << std::endl;

    int* null_int_ptr = nullptr;
    double* null_double_ptr = nullptr;

    std::cout << std::endl;
    print_nullptr("null_int_ptr", null_int_ptr);
    print_nullptr("null_double_ptr", null_double_ptr);
    std::cout << "Разыменование указетелей, инициализированных nullptr, невозможно." << std::endl;


    std::cout << "\n\n2. Выделение памяти с подходящими значениями:\n" << std::endl;

    int* int_ptr = new int(100);
    double* double_ptr = new double(3.14);

    print_ptr("int_ptr", int_ptr);
    print_ptr("double_ptr", double_ptr);


    std::cout << "\n\n3. Просмотр значений массива с помощью арифметики указателей:\n" << std::endl;

    int* array_ptr = new int[5] {1, 2, 3, 4, 5};

    for (int i = -1; i < 6; i++) {
        print_ptr("array_ptr[" + std::to_string(i) + "]", array_ptr + i);
    }


    std::cout << "\n\n4. Изменение значения через доступ к отдельным байтам:\n" << std::endl;

    print_ptr_with_memory("int_ptr", int_ptr, sizeof(int));

    unsigned char* bytes = reinterpret_cast<unsigned char*>(int_ptr);
    bytes[0] = 0x2C;
    bytes[1] = 0x01;

    print_ptr_with_memory("int_ptr", int_ptr, sizeof(int));


    std::cout << "\n\n5. Потеря указателя и доступ через арифметику указателей:\n" << std::endl;

    int* temp_ptr = array_ptr + 4;
    array_ptr = nullptr;

    print_nullptr("array_ptr", array_ptr);
    for (int i = 4; i >= 0; i--) {
        print_ptr("temp_ptr - " + std::to_string(i), temp_ptr - i);
    }


    std::cout << "\n\n6. Освобождение памяти и наблюдение за содержимым:\n" << std::endl;

    print_ptr_with_memory("int_ptr", int_ptr, sizeof(int));

    temp_ptr = int_ptr;
    delete int_ptr;

    print_ptr_with_memory("temp_ptr", temp_ptr, sizeof(int));

    temp_ptr = new int(500);

    print_ptr_with_memory("temp_ptr", temp_ptr, sizeof(int));


    std::cout << "\n\n7. Свой эксперимент:" << std::endl;
    
    int hex = 0x2b2b43;
    int_ptr = &hex;
    char* char_ptr = reinterpret_cast<char*>(&hex);

    print_ptr_with_memory("int_ptr", int_ptr, sizeof(int));
    print_ptr_with_memory("char_ptr", char_ptr, sizeof(char) * 4);
}
