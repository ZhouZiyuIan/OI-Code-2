//
// Created by 118 on 25-7-9.
//
#pragma GCC optimize(3,"Ofast")
#include<stdio.h>
int min(int a, int b) {
    return a < b ? a : b;
}
int T, m, n, mu[10000001], prime[10000001], cnt, sum[10000001], f[10000001];
bool vis[10000001];
void get_mu() {
    mu[1] = 1;
    for (int i = 2; i < 10000001; ++i) {
        if (!vis[i]) {
            mu[i] = -1;
            prime[++cnt] = i;
        }
        for (int j = 1; j <= cnt && i * prime[j] < 10000001; ++j) {
            vis[i * prime[j]] = 1;
            if (i % prime[j] == 0) {
                break;
            }
            else {
                mu[i * prime[j]] = -mu[i];
            }
        }
    }
    for (int i = 1; i <= cnt; ++i) {
        for (int j = 1; prime[i] * j < 10000001; ++j) {
            f[prime[i] * j] += mu[j];
        }
    }
    for (int i = 1; i < 10000001; ++i) {
        sum[i] = sum[i - 1] + f[i];
    }
}
long long calc(int a, int b) {
    int max_rep = min(a, b);
    long long ans = 0;
    for (int l = 1, r; l <= max_rep; l = r + 1) {
        r = min(a / (a / l), b / (b / l));
        ans+=(1ll * a / (1ll * l)) * (1ll * b / (1ll * l)) * (sum[r] - sum[l - 1]);
    }
    return ans;
}
int main() {
    scanf("%d", &T);
    get_mu();
    while (T--) {
        scanf("%d%d",&m,&n);
        printf("%lld\n",calc(m,n));
    }
}