#include "tasks_2.h"
#include <iostream>
#include <string>

static void remove_between_commas(std::string& s) {
    std::string result = "";
    bool f = false;

    for (char c : s) {
        if (c == ',') {
            f = !f;
            continue;
        }

        if (!f) {
            result += c;
        }
    }

    s = result;
}

void task_205() {
    int n;
    std::cin >> n;
    std::cin.get();

    for (int i = 0; i < n; i++) {
        std::string s;
        getline(std::cin, s);
        remove_between_commas(s);
        std::cout << s << std::endl;
    }
}
