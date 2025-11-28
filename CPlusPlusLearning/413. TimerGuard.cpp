#include "tasks_4.h"
#include <iostream>
#include <chrono>
#include <string>
#include <thread>

static class TimerGuard {
private:
    std::string message;
    std::ostream& out;
    std::chrono::time_point<std::chrono::high_resolution_clock> start;

public:
    TimerGuard(std::string message = "", std::ostream& out = std::cout)
        : message(std::move(message)), out(out),
        start(std::chrono::high_resolution_clock::now())
    {
    }

    ~TimerGuard() {
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> diff = end - start;
        out << message << " " << diff.count() << "\n";
    }
};

static void someWork() {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

void task_413() {
    {
        TimerGuard timer("Work elapsed:");
        someWork();
    }

    {
        TimerGuard timer("Custom message:", std::cerr);
        someWork();
    }
}
