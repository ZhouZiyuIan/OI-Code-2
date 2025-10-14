#include <iostream>
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <cstdlib>
using namespace std;

int main() {
    freopen("input.in", "w", stdout);
    int n = 1000;  // 选择较大的n，但不要太大以便于调试
    int p = 2;     // 选择适当的p，比如2

    // 生成交替序列：1,2,1,2,...，这样每个地址都会频繁出现
    vector<int> a;
    for (int i = 0; i < n; i++) {
        if (i % 2 == 0) {
            a.push_back(1);
        } else {
            a.push_back(2);
        }
    }

    // 输出
    cout << n << " " << p << endl;
    for (int i = 0; i < n; i++) {
        cout << a[i] << " ";
    }
    cout << endl;

    return 0;
}