#include "tasks_3.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

static string Join(const vector<string>& tokens, char delimiter) {
    if (tokens.empty()) {
        return "";
    }
    string result = tokens[0];
    for (size_t i = 1; i < tokens.size(); i++) {
        result += delimiter;
        result += tokens[i];
    }
    return result;
}

void task_308() {
    vector<string> test = { "What", "is", "your", "name?" };
    cout << Join(test, '_') << endl;
}
