//
// Created by 118 on 25-7-8.
//
#pragma GCC optimize(2,3,"Ofast")
#include <iostream>
using namespace std;
constexpr int MOD = 1e9+7;
long long x, ans, m, d;
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> x;
    if (x & 1) {
        d = 3;
    }
    else {
        d = 0;
    }
    x %= MOD;
    m = x;
    ans = 26 * m + d;
    ans %= MOD;
    m *= x;
    m %= MOD;
    ans -= 111 * m;
    ans %= MOD;
    m *= x;
    m %= MOD;
    ans += 106 * m;
    ans %= MOD;
    ans *= 41666667;
    ans %= MOD;
    cout << ans;
}