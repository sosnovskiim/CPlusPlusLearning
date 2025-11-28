#include "tasks_4.h"
#include <iostream>
#include <vector>

static class Logger {
private:
    static int counter;
    const int id;

public:
    Logger() : id(++counter) {
        std::cout << "Logger(): " << id << "\n";
    }

    Logger(const Logger& other) : id(++counter) {
        std::cout << "Logger(const Logger&): " << id << " " << other.id << "\n";
    }

    Logger(Logger&& other) : id(++counter) {
        std::cout << "Logger(Logger&&): " << id << " " << other.id << "\n";
    }

    Logger& operator = (const Logger& other) {
        std::cout << "Logger& operator = (const Logger&): " << id << " " << other.id << "\n";
        return *this;
    }

    Logger& operator = (Logger&& other) {
        std::cout << "Logger& operator = (Logger&&): " << id << " " << other.id << "\n";
        return *this;
    }

    ~Logger() {
        std::cout << "~Logger(): " << id << "\n";
    }
};

void task_422() {
    int n;
    std::cin >> n;
    std::vector<Logger*> loggers;
    for (int i = 0; i < n; ++i) {
        loggers.push_back(new Logger());
    }
    for (int i = n - 1; i >= 0; --i) {
        delete loggers[i];
    }
}
