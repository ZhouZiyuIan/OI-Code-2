#include <bits/stdc++.h>
using namespace std;
const int N = 3e5 + 10;
const int mod = 1e9 + 7;
int n, a[N];
using ii = pair<int, int>;
int dp[N];
int sum[N];
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];//第19行
    set<ii> s;
    sum[0] = 1;
    for (int i = 1, res = 0; i <= n; ++i) {
        ii u;
        while (!s.empty()) {
            u = (*s.rbegin());//*rbegin 是反向迭代器
            if (u.first > a[i]) {
                res = (res - dp[u.second] + mod) % mod;
                s.erase(u);
            } else break;
        }
        if (s.empty()) dp[i] = sum[i - 1];
        else dp[i] = (res + sum[i-1] - sum[u.second]) % mod;
        if (dp[i] < 0) dp[i] += mod;
        sum[i] = (sum[i - 1] + dp[i]) % mod;
        s.insert({a[i], i});
        res = (res + dp[i]) % mod;
    }
    int ans = 0;
    for (ii u: s) ans = (ans + dp[u.second]) % mod;
    cout << ans << endl;
    return 0;
}
