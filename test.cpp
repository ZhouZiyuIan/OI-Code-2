#pragma GCC optimize (3, "Ofast", "inline")
#include <iostream>
#include <vector>
using namespace std;
long long p;
vector<long long> factors;
long long fpow(long long base, long long exp, long long mod) {
    long long res = 1;
    base %= mod;
    while (exp) {
        if (exp & 1) {
            res = res * base % mod;
        }
        base = base * base % mod;
        exp >>= 1;
    }
    return res;
}
void get(long long n) {
    for (long long i = 2; i * i <= n; ++i) {
        if (n % i == 0) {
            factors.emplace_back(i);
            while (n % i == 0) {
                n /= i;
            }
        }
    }
    if (n > 1) {
        factors.emplace_back(n);
    }
}
bool chk(long long g, long long p) {
    for (long long q : factors) {
        if (fpow(g, (p - 1) / q, p) == 1) {
            return 0;
        }
    }
    return 1;
}
int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> p;
    get(p - 1);
    for (long long g = 2; g < p; ++g) {
        if (chk(g, p)) {
            cout << g << endl;
            break;
        }
    }
}
