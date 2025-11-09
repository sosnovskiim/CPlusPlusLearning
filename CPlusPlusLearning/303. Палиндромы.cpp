#include "tasks_3.h"
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

void task_303() {
    string s;
    getline(cin, s);

    s.erase(remove(s.begin(), s.end(), ' '), s.end());

    string reversed = s;
    reverse(reversed.begin(), reversed.end());

    if (s == reversed) {
        cout << "YES" << endl;
    }
    else {
        cout << "NO" << endl;
    }
}
