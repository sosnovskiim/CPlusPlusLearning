#include "tasks_3.h"
#include <windows.h>
#include <exception>
#include <functional>
#include <optional>
#include <thread>
#include <chrono>
#include <iostream>

static void Sleep(int sleepTime) {
    std::this_thread::sleep_for(std::chrono::milliseconds(sleepTime));
}

template <typename Result, typename Exception = std::exception>
static std::optional<Result> DoWithRetry(std::function<Result()> func,
    int retryCount, int sleepTime, bool throwLast) {
    int attemptsLeft = retryCount + 1;
    while (attemptsLeft > 0) {
        try {
            return func();
        }
        catch (const Exception&) {
            attemptsLeft--;
            if (attemptsLeft == 0) {
                if (throwLast) {
                    throw;
                }
                else {
                    return std::optional<Result>();
                }
            }
            else {
                Sleep(sleepTime);
            }
        }
    }
    return std::optional<Result>();
}

static std::string UnreliableService(int& callCount) {
    callCount++;
    std::cout << "Попытка вызова #" << callCount << std::endl;
    if (callCount < 3) {
        throw std::runtime_error("Сервис временно недоступен");
    }
    return "Успешный результат";
}

static std::string AlwaysFails(int& callCount) {
    callCount++;
    std::cout << "Попытка вызова #" << callCount << std::endl;
    throw std::runtime_error("Всегда падает");
}

void task_310() {
    SetConsoleOutputCP(1251);

    try {
        int callCount1 = 0;
        auto func1 = [&callCount1]() { return UnreliableService(callCount1); };

        auto result1 = DoWithRetry<std::string, std::runtime_error>(
            func1, 3, 100, false);

        if (result1) {
            std::cout << "Результат: " << *result1 << std::endl;
        }
        else {
            std::cout << "Пустой результат" << std::endl;
        }
    }
    catch (const std::exception& e) {
        std::cout << "Исключение: " << e.what() << std::endl;
    }

    std::cout << "\nВсе попытки неудачны (throwLast = false):" << std::endl;
    try {
        int callCount2 = 0;
        auto func2 = [&callCount2]() { return AlwaysFails(callCount2); };

        auto result2 = DoWithRetry<std::string, std::runtime_error>(
            func2, 2, 100, false);

        if (result2) {
            std::cout << "Результат: " << *result2 << std::endl;
        }
        else {
            std::cout << "Пустой результат (как и ожидалось)" << std::endl;
        }
    }
    catch (const std::exception& e) {
        std::cout << "Исключение: " << e.what() << std::endl;
    }
}
