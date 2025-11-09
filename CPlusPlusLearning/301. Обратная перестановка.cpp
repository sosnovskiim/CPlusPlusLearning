#include "tasks_3.h"
#include <iostream>
#include <vector>

using namespace std;

void task_301() {
    int n;
    cin >> n;

    vector<int> a(n + 1);
    vector<int> b(n + 1);

    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    for (int k = 1; k <= n; k++) {
        b[a[k]] = k;
    }

    for (int i = 1; i <= n; i++) {
        cout << b[i] << " ";
    }
    cout << endl;
}
