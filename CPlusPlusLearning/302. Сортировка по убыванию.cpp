#include "tasks_3.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

void task_302() {
    vector<string> lines;
    string line;
    while (getline(cin, line)) {
        lines.push_back(line);
    }
    sort(lines.begin(), lines.end(), greater<string>());
    for (const auto& str : lines) {
        cout << str << endl;
    }
}
