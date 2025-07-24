//
// Created by 118 on 25-7-11.
//
#include <stdio.h>
int n, C[16], P[16], L[16], f;
int exgcd(int a, int b, int& x, int& y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    int ans = exgcd(b, a % b, x, y);
    int cur_x = x;
    x = y;
    y = cur_x - (a / b) * y;
    return ans;
}
int main() {
    scanf("%d",&n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d%d%d", &C[i], &P[i], &L[i]);
    }
    for (int i = C[n]; i < 1000001; ++i) {
        f = 0;
        for (int j = 1; j < n; ++j) {
            for (int k = j + 1; k <= n; ++k) {
                int a = P[k] - P[j];
                int b = i;
                int c = C[j] - C[k];
                int x, y, gcd, minx;
                if (a < 0) {
                    a = -a;
                    c = -c;
                }
                gcd = exgcd(a, b, x, y);
                if (c % gcd != 0) {
                    continue;
                }
                minx = ((x * (c / gcd)) % (b / gcd) + (b / gcd)) % (b / gcd);
                if (minx <= (L[j] < L[k] ? L[j] : L[k])) {
                    f = 1;
                    break;
                }
                if (f == 1) {
                    break;
                }
            }
        }
        if (f == 0) {
            printf("%d", i);
            break;
        }
    }
}