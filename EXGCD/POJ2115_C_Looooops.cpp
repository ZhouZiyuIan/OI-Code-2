//
// Created by 118 on 25-7-11.
//
#include <stdio.h>
typedef long long ll;
ll exgcd(ll a,ll b,ll &x,ll &y) {
    if(b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    ll r = exgcd(b, a % b, x, y);
    ll t = x;
    x = y;
    y = t - a / b * y;
    return r;
}
ll A, B, C, k, a, b, n, x, y, d;
int main() {
    for (;;) {
        scanf("%lld%lld%lld%lld", &A, &B, &C, &k);
        if (A == 0 && B == 0 && C == 0 && k == 0) {
            break;
        }
        a = C;
        b = B - A;
        n = 1ll << k;
        d = exgcd(a, n, x, y);
        if (b % d) {
            putchar(70);
            putchar(79);
            putchar(82);
            putchar(69);
            putchar(86);
            putchar(69);
            putchar(82);
        }
        else {
            x = (x * (b / d)) % n;
            x = (x % (n / d) + n / d) % (n / d);
            printf("%lld", x);
        }
        putchar(10);
    }
}