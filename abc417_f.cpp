// Problem: F - Random Gathering
// Contest: AtCoder - AtCoder Beginner Contest 417
// URL: https://atcoder.jp/contests/abc417/tasks/abc417_f
// Memory Limit: 1024 MB
// Time Limit: 3000 ms
// Input Type: {"type":"stdin"}
// Output Type: {"type":"stdout"}
// Start Programming Time: 2025-08-02 20:00:12
// By: FkZ
// 
// Powered by CP Editor (https://cpeditor.org)
#include <stdio.h>
const int MOD = 998244353;
long long fpow(long long a, long long e) {
    long long r = 1;
    while (e) {
        if (e & 1) r = r * a % MOD;
        a = a * a % MOD;
        e >>= 1;
    }
    return r;
}
int N, M, L, R, tag[800001];
long long A[200001], sum[800001], val[800001];
void build(int k, int l, int r) {
    if (l == r) {
        sum[k] = A[l] % MOD;
        tag[k] = 0;
        return;
    }
    int mid = (l + r) >> 1;
    build(k << 1, l, mid);
    build(k << 1 | 1, mid + 1, r);
    sum[k] = (sum[k << 1] + sum[k << 1 | 1]) % MOD;
    tag[k] = 0;
}
void pushdown(int k, int l, int r) {
    if (!tag[k]) return;
    int mid = (l + r) >> 1;
    tag[k << 1] = 1;
    val[k << 1] = val[k];
    sum[k << 1] = val[k] * (mid - l + 1) % MOD;
    tag[k << 1 | 1] = 1;
    val[k << 1 | 1] = val[k];
    sum[k << 1 | 1] = val[k] * (r - mid) % MOD;
    tag[k] = 0;
}
void upd(int k, int l, int r, int L, int R, long long c) {
    if (L <= l && r <= R) {
        tag[k] = 1;
        val[k] = c;
        sum[k] = c * (r - l + 1) % MOD;
        return;
    }
    pushdown(k, l, r);
    int mid = (l + r) >> 1;
    if (L <= mid) {
        upd(k << 1, l, mid, L, R, c);
    }
    if (mid < R) {
        upd(k << 1 | 1, mid + 1, r, L, R, c);
    }
    sum[k] = (sum[k << 1] + sum[k << 1 | 1]) % MOD;
}
long long que(int k, int l, int r, int L, int R) {
    if (L <= l && r <= R) {
        return sum[k];
    }
    pushdown(k, l, r);
    int mid = (l + r) >> 1;
    long long ans = 0;
    if (L <= mid) {
        ans = (ans + que(k << 1, l, mid, L, R)) % MOD;
    }
    if (mid < R) {
        ans = (ans + que(k << 1 | 1, mid + 1, r, L, R)) % MOD;
    }
    return ans;
}
int main() {
    scanf("%d%d", &N, &M);
    for (int i = 1; i <= N; ++i) {
        scanf("%lld", &A[i]);
    }
    build(1, 1, N);
    for (int i = 0; i < M; ++i) {
        scanf("%d%d", &L, &R);
        long long c = que(1, 1, N, L, R) * fpow(R - L + 1, MOD - 2) % MOD;
        upd(1, 1, N, L, R, c);
    }
    for (int i = 1; i <= N; ++i) {
        long long ans = que(1, 1, N, i, i);
        printf("%lld ", ans);
    }
}