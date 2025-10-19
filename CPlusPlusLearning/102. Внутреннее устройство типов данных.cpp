#include "tasks_1.h"

#define NOMINMAX
#include <windows.h>

#include <bitset>
#include <iostream>
#include <iomanip>
#include <string>

template<typename T>
static void print_int_type_info(const std::string& type_name) {
    std::cout << std::setw(20) << type_name << std::setw(7) << sizeof(T);
    std::cout << std::numeric_limits<T>::min() << " ... " << std::numeric_limits<T>::max() << std::endl;
}

template<typename T>
static void print_float_type_info(const std::string& type_name) {
    std::cout << std::setw(13) << type_name << std::setw(7) << sizeof(T);
    if (typeid(T) == typeid(float)) {
        std::cout << FLT_DIG;
    } else if (typeid(T) == typeid(double)) {
        std::cout << DBL_DIG;
    } else if (typeid(T) == typeid(long double)) {
        std::cout << LDBL_DIG;
    } else {
        std::cout << 0;
    }
    std::cout << std::endl;
}

template<typename T>
static void print_binary(T value) {
    const unsigned char* bytes = reinterpret_cast<const unsigned char*>(&value);

    std::cout << std::setw(8) << value;
    for (size_t i = 0; i < sizeof(T); i++) {
        std::cout << std::bitset<8>(bytes[i]) << " ";
    }
    std::cout << std::endl;
}

void task_102() {
    SetConsoleOutputCP(1251);

    std::cout << "1. Целочисленные типы:\n" << std::endl;

    std::cout << std::left << std::setw(20) << "Название" << "Байты  Диапазон" << std::endl;

    print_int_type_info<short>("short");
    print_int_type_info<unsigned short>("unsigned short");
    print_int_type_info<int>("int");
    print_int_type_info<unsigned int>("unsigned int");
    print_int_type_info<long long>("long long");
    print_int_type_info<unsigned long long>("unsigned long long");

    std::cout << "\nВнутреннее представление:" << std::endl;

    print_binary(1000);
    print_binary(-1000);

    std::cout << "\nПереполнение типов:" << std::endl;

    short short_test = 32767;
    std::cout << std::left << std::setw(16);
    std::cout << "short" << short_test << " + 1 = ";
    short_test++;
    std::cout << short_test << std::endl;

    unsigned short unsigned_short_test = 65535;
    std::cout << std::left << std::setw(16);
    std::cout << "unsigned short" << unsigned_short_test << " + 1 = ";
    unsigned_short_test++;
    std::cout << unsigned_short_test << std::endl;


    std::cout << "\n\n2. Вещественные типы:\n" << std::endl;

    std::cout << std::left << std::setw(13) << "Название" << "Байты  Точность" << std::endl;

    print_float_type_info<float>("float");
    print_float_type_info<double>("double");
    print_float_type_info<long double>("long double");

    std::cout << "\nВнутреннее представление:" << std::endl;

    print_binary(1.0f);
    print_binary(-1.0f);
    print_binary(0.1f);

    std::cout << "\nОсобые значения:" << std::endl;

    float zero = 0.0f;
    float inf_test = 1.0f / zero;
    float nan_test = zero / zero;

    std::cout << "1.0 / 0.0 = " << inf_test << std::endl;
    std::cout << "0.0 / 0.0 = " << nan_test << std::endl;
    std::cout << "inf == inf: " << std::boolalpha << (inf_test == inf_test) << std::endl;
    std::cout << "nan == nan: " << std::boolalpha << (nan_test == nan_test) << std::endl;

    std::cout << "\nПроблемы точности:" << std::endl;

    std::cout << "0.1f      " << std::setprecision(20) << 0.1f << std::endl;
    std::cout << "0.1       " << std::setprecision(20) << 0.1 << std::endl;
    std::cout << "0.1f x10  " << (0.1f + 0.1f + 0.1f + 0.1f + 0.1f + 0.1f + 0.1f + 0.1f + 0.1f + 0.1f) << std::endl;


    std::cout << "\n\n3. Булевый тип:\n" << std::endl;

    std::cout << "Размер bool - " << sizeof(bool) << " байт" << std::endl;

    std::cout << "\nВнутреннее представление:" << std::endl;
    print_binary(true);
    print_binary(false);


    std::cout << "\n\n4. Символы:\n" << std::endl;

    std::cout << "Размер char - " << sizeof(char) << " байт" << std::endl;
    std::cout << "Размер unsigned char - " << sizeof(unsigned char) << " байт" << std::endl;

    std::cout << "\nВнутреннее представление:" << std::endl;

    print_binary('A');
    print_binary('B');
    print_binary('C');

    std::cout << "\nПереполнение типов:" << std::endl;

    char char_test = 127;
    std::cout << std::left << std::setw(15);
    std::cout << "char" << "'" << char_test << "' + 1 = '";
    char_test++;
    std::cout << char_test << "'" << std::endl;

    unsigned char unsigned_char_test = 255;
    std::cout << std::left << std::setw(15);
    std::cout << "unsigned char" << "'" << unsigned_char_test << "' + 1 = '";
    unsigned_char_test++;
    std::cout << unsigned_char_test << "'" << std::endl;


    std::cout << "\n\n5. Строки:\n" << std::endl;

    std::cout << "Размер std::string - " << sizeof(std::string) << " байт" << std::endl;

    std::string string_test = "It's just a test string.";

    std::cout << std::endl;
    std::cout << string_test << std::endl;
    std::cout << "Длина: " << string_test.length() << std::endl;
    std::cout << "Вместимость: " << string_test.capacity() << std::endl;

    std::cout << "\nВнутреннее представление:" << std::endl;

    print_binary("Hi!");
    print_binary("It's just a test string.");

    std::cout << "\nПредставление в виде массива символов:" << std::endl;

    const char* cstr = string_test.c_str();

    std::cout << cstr << "  ";
    for (size_t i = 0; i < string_test.length(); i++) {
        std::cout << std::hex << static_cast<int>(cstr[i]) << " ";
    }
    std::cout << std::endl;
}
