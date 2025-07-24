//
// Created by 118 on 25-7-11.
//
#include <stdio.h>
int N, a[11], f[65541], g, ans;
int gcd(int x, int y) {
    if (x < y) {
        int tmp = x;
        x = y;
        y = tmp;
    }
    return y == 0 ? x : gcd(y, x % y);
}
int main() {
    scanf("%d", &N);
    for (int i = 1; i <= N; i++) {
        scanf("%d", &a[i]);
        g = gcd(g, a[i]);
    }
    f[0] = 1;
    for (int i = 1; i <= 65535; i++) {
        for (int j = 1; j <= N; j++) {
            if (i >= a[j]) {
                f[i] |= f[i - a[j]];
            }
        }
        if (f[i] == 0) {
            ans = i;
        }
    }
    printf("%d", g == 1 ? ans : 0);
}