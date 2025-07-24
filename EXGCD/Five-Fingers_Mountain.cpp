//
// Created by 118 on 25-7-11.
//
#include <stdio.h>
int T;
long long exgcd(long long a,long long b,long long &x,long long &y){
    if(b == 0){
        x = 1;
        y = 0;
        return a;
    }
    int r = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return r;
}
int main() {
    scanf("%d", &T);
    while (T--) {
        long long n,d,x,y,a,b;
        scanf("%lld%lld%lld%lld", &n, &d, &x, &y);
        int gcd = exgcd(n, d, a, b);
        if ((y - x) % gcd) {
            printf("Impossible");
        }
        else {
            b *= (y - x) / gcd;
            n /= gcd;
            printf("%lld", (b % n + n) % n);
        }
        putchar(10);
    }
}