#include "tasks_3.h"
#include <iostream>
#include <string>

using namespace std;

void task_304() {
    string word;
    cin >> word;

    string code;
    code += word[0];

    for (int i = 1; i < word.size(); i++) {
        char c = word[i];
        if (string("aehiouwy").find(c) != string::npos) continue;

        if (string("bfpv").find(c) != string::npos) code += '1';
        else if (string("cgjkqsxz").find(c) != string::npos) code += '2';
        else if (string("dt").find(c) != string::npos) code += '3';
        else if (c == 'l') code += '4';
        else if (string("mn").find(c) != string::npos) code += '5';
        else if (c == 'r') code += '6';
    }

    string cleaned;
    if (!code.empty()) {
        cleaned += code[0];
        for (int i = 1; i < code.size(); i++) {
            if (code[i] != code[i - 1]) {
                cleaned += code[i];
            }
        }
    }

    string result = cleaned.substr(0, 4);
    while (result.size() < 4) {
        result += '0';
    }

    cout << result << endl;
}