//
// Created by 118 on 25-7-8.
//
#include <stdio.h>
const long long MOD = 998244853;
long long n, m, f[50001][4001], lent, sum, lt[1001], rt[1001], len_tot, ans, pre_sum;
char s[50001], t[1001], all_t[4001];
int main() {
    scanf("%lld%lld%s", &n, &m, s + 1);
    for (long long i = 1; i <= m; ++i) {
        scanf("%s",t + 1);
        lt[i] = ++len_tot;
        f[0][lt[i]] = 1;
        for (lent = 0; t[lent + 1]; ++lent) {
            all_t[++len_tot] = t[lent + 1];
        }
        rt[i] = len_tot;
    }
    for (long long i = 1; i <= n; ++i) {
        for (long long j = 1; j <= m; ++j) {
            f[i][lt[j]] = 1;
        }
        if (s[i] == '*') {
            for (long long j = 1; j <= m; ++j) {
                pre_sum = 0;
                for (long long k = lt[j]; k <= rt[j]; ++k) {
                    pre_sum += f[i - 1][k];
                    pre_sum %= MOD;
                    f[i][k] += pre_sum;
                    f[i][k] %= MOD;
                }
            }
        }
        else {
            for (long long j = 1; j <= m; ++j) {
                for (long long k = lt[j] + 1; k <= rt[j]; ++k) {
                    if (s[i] == all_t[k]) {
                        f[i][k] = f[i - 1][k - 1];
                    }
                }
            }
        }
        for (long long j = 1; j <= m; ++j) {
            ans += f[i][rt[j]];
            ans %= MOD;
        }
    }
    printf("%lld\n", (ans + MOD) % MOD);
    return 0;
}