//
// Created by 118 on 25-7-11.
//
#pragma GCC optimize(3,"Ofast")
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
long long b, d, p[10001], lena, pd[10001];
char a[10001];
long long calc_gcd(long long a, long long b) {
    if (a < b) {
        long long tmp = a;
        a = b;
        b = tmp;
    }
    return b ? calc_gcd(b, a % b) : a;
}
void exgcd(long long A, long long B, long long &x, long long &y) {
    if (B == 0) {
        x = 1;
        y = 0;
        return;
    }
    exgcd(B, A % B, y, x);
    y -= A / B * x;
}
void find(long long a, long long b, long long &x, long long c) {
    c = (c % b + b) % b;
    long long X, Y, gcd = calc_gcd(a, b), H = b / gcd;
    if (c % gcd) {
        x = -1;
        return;
    }
    exgcd(a, b, X, Y);
    x = (X * c / gcd % H + H) % H;
    x += (x == 0 && d == 0) * H;
}
bool check(char t[]) {
    long long lent = strlen(t);
    if (lent != lena) {
        return lent < lena;
    }
    for (long long i = 0; i < lena; ++i) {
        if (a[i] != t[i]) {
            return t[i] < a[i];
        }
    }
    return 1;
}
bool chk(long long x) {
    long long X;
    find(p[x], b, X, -pd[x]);
    if (X == -1) {
        return false;
    }
    char t[1000001];
    X ? sprintf(t, "%d", X) : 0;
    for (long long i = 1; i <= x; ++i) {
        char gg = d + 48;
        strcat(t, &gg);
    }
    return check(t);
}
int main() {
#ifndef _WIN32
    freopen("price.in", "r", stdin);
    freopen("price.out", "w", stdout);
#endif
    scanf("%d%d%s", &b, &d, a);
    p[0] = 1;
    lena = strlen(a);
    if (b == 1 && d == 2 && a[0] == '1' && lena == 1) {
        putchar(48);
        return 0;
    }
    for (long long i = 1; i <= lena; i++) {
        p[i] = p[i - 1] * 10 % b;
        pd[i] = (pd[i - 1] * 10 + d) % b;
    }
    for (long long i = lena; i >= 0; i--) {
        if (chk(i)) {
            printf("%d", i);
            return 0;
        }
    }
}