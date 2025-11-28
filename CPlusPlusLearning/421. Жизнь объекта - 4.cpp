#include "tasks_4.h"
#include <iostream>

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

void task_421() {
    Logger logger1;
    Logger* logger2 = new Logger();
    Logger logger3;
    delete logger2;
}
