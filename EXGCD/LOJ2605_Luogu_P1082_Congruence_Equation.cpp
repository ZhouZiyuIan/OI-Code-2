//
// Created by 118 on 25-7-11.
//
#include <stdio.h>
int a, b, x, y;
void exgcd(int A, int B) {
    if (B==0) {
        x = 1;
        y = 0;
        return;
    }
    exgcd(B, A % B);
    long long cur_x = x;
    x = y;
    y = cur_x - A / B * y;
}
int main() {
    scanf("%d%d", &a, &b);
    exgcd(a, b);
    x = (x % b + b) % b;
    printf("%d\n", x);
}