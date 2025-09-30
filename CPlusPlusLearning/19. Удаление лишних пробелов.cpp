#include "tasks_0.h"
#include <iostream>
#include <string>

void remove_extra_spaces(std::string& s) {
	std::string result;
	bool is_word = false;

	for (char c : s) {
		if (c != ' ') {
			if (is_word) {
				result += c;
			} else {
				if (!result.empty()) {
					result += ' ';
				}
				result += c;
				is_word = true;
			}
		} else {
			is_word = false;
		}
	}

	s = result;
}

void task_0_19() {
	int n;
	std::cin >> n;
	std::cin.get();

	for (int i = 0; i < n; i++) {
		std::string s;
		getline(std::cin, s);

		remove_extra_spaces(s);

		std::cout << s << std::endl;
	}
}
