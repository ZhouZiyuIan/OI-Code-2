//
// Created by 118 on 25-7-29.
//
#include <stdio.h>
int abs(int _X) {
	return _X < 0 ? -_X : _X;
}
int gcd(int a, int b) {
	return b == 0 ? a : gcd(b, a % b);
}
int n, m, p, S, s;
int main() {
	scanf("%d%d%d", &n, &m, &p);
	S = (p * m) / 2;
	++S;
	s = p + gcd(n, m) + gcd(abs(p - n), m);
	s /= 2;
	printf("%d", S - s);
}