#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;
vector<vector<ll>> cumSums, dp;
vector<ll> total_sum;
vector<int> P, A, B;
int N, Q;
ll F(int i, ll x) {
    if (i > N) {
        return x;
    }
    ll need = x - 500;
    if (need < 0) need = 0;
    vector<ll>& vec = cumSums[i];
    auto it = lower_bound(vec.begin(), vec.end(), need);
    if (it == vec.end()) {
        return x - total_sum[i];
    }
    int k = it - vec.begin();
    ll S = vec[k];
    ll mood = x - S;
    if (mood < 0) {
        mood = 0;
    }
    int nxtidx = i + k;
    if (nxtidx > N) {
        return mood;
    }
    if (mood <= 500) {
        return dp[nxtidx][mood];
    }
    return F(nxtidx, mood);
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    P.resize(N+1);
    A.resize(N+1);
    B.resize(N+1);
    for (int i = 1; i <= N; ++i) {
        cin >> P[i] >> A[i] >> B[i];
    }
    cumSums.resize(N+1);
    total_sum.resize(N+1, 0);
    for (int i = 1; i <= N; ++i) {
        vector<ll> vec;
        vec.emplace_back(0);
        ll s = 0;
        for (int j = i; j <= N; ++j) {
            s += B[j];
            vec.emplace_back(s);
        }
        cumSums[i] = vec;
        total_sum[i] = s;
    }
    dp.resize(N+2, vector<ll>(501, 0));
    for (int v = 0; v <= 500; ++v) {
        dp[N+1][v] = v;
    }
    for (int i = N; i >= 1; --i) {
        for (int v = 0; v <= 500; ++v) {
            if (v <= P[i]) {
                ll new_v = (ll)v + A[i];
                if (new_v <= 500) {
                    dp[i][v] = dp[i+1][new_v];
                }
                else {
                    if (i+1 <= N) {
                        dp[i][v] = F(i+1, new_v);
                    }
                    else {
                        dp[i][v] = new_v;
                    }
                }
            }
            else {
                int new_v = (v >= B[i]) ? (v - B[i]) : 0;
                dp[i][v] = dp[i+1][new_v];
            }
        }
    }
    cin >> Q;
    while (Q--) {
        ll x;
        cin >> x;
        if (x <= 500) {
            cout << dp[1][x] << '\n';
        }
        else {
            cout << F(1, x) << '\n';
        }
    }
}