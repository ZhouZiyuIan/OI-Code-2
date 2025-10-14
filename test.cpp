#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef long long i64;
int cmp(const void *pa, const void *pb) {
    int a = *(const int*)pa;
    int b = *(const int*)pb;
    if (a < b) return -1;
    if (a > b) return 1;
    return 0;
}
int main() {
    int n;
    static int prec[200010][3], a[200010];
    static char str[200010];
    i64 ans = 0;
    scanf("%d%s", &n, str + 1);
    memset(prec, 0, sizeof(prec));
    for (int i = 1; i <= n; ++i) {
        prec[i][0] = prec[i-1][0];
        prec[i][1] = prec[i-1][1];
        prec[i][2] = prec[i-1][2];
        prec[i][str[i] - 'a']++;
    }
    i64 s1 = 0, s2 = 0;
    for (int o = 0; o < 3; ++o) {
        for (int i = 0; i <= n; ++i) {
            a[i] = prec[i][o] - prec[i][(o + 1) % 3];
        }
        qsort(a, n + 1, sizeof(int), cmp);
        for (int i = 0; i < n; ++i) {
            i64 diff = (i64)(a[i+1] - a[i]);
            s1 += diff * (i64)(i + 1) * (i64)(n - i);
        }
    }
    for (int c = 0; c < 3; ++c) {
        int j = 1;
        for (int i = 1; i <= n; ++i) {
            int cur = str[i] - 'a' == c, nxt = i == n ? -1 : str[i+1] - 'a' == c;
            if (i == n || cur != nxt) {
                if (!cur) {
                    for (int o = 0; o < 3; ++o) {
                        int N = 0;
                        for (int k = j - 1; k <= i; ++k) {
                            ++N;
                            a[N] = prec[k][o] - prec[k][(o + 1) % 3];
                        }
                        qsort(a + 1, N, sizeof(int), cmp);
                        for (int k = 1; k < N; ++k) {
                            i64 diff = a[k+1] - a[k], cont = diff * (i64)k * (i64)(N - k);
                            s1 -= cont;
                            if (o == (c + 1) % 3) s2 += cont;
                        }
                    }
                }
                j = i + 1;
            }
        }
    }
    int j = 1;
    for (int i = 1; i <= n; ++i) {
        if (i == n || str[i+1] != str[i]) {
            int N = i - j + 1;
            for (int k = 1; k <= N; ++k) {
                s1 += (i64)k * (i64)(k + 1);
                s2 -= (i64)k * (i64)(k + 1);
            }
            j = i + 1;
        }
    }
    ans = s1 / 2 + s2;
    printf("%lld", ans);
}
