//
// Created by 118 on 25-7-27.
//
#include <stdio.h>
#include <ctype.h>
#ifdef _WIN64
#define getchar_unlocked() _getchar_nolock()
#define putchar_unlocked(_c) _putchar_nolock(_c)
#endif
typedef long long ll;
void read(int* w) {
	int f = 1, x = 0;
	char s = getchar_unlocked();
	while (!isdigit(s)) {
		if (s == 45) f = -f;
		s = getchar_unlocked();
	}
	do {
		x = (x << 1) + (x << 3) + (s ^ 48);
		s = getchar_unlocked();
	} while (isdigit(s));
	*w = x * f;
}
void write(ll x) {
	if (x < 0) {
		x = -x;
		putchar_unlocked(45);
	}
	if (x > 9) write(x / 10);
	putchar_unlocked(x % 10 + 48);
}
int n, k, ava2[8]={0, 1, 0, 1, 1, 0, 0, 0};
long long cnt[8]={0, 1 << 19, 32, 8, 1 << 13, 4, 2, 32};
int main() {
	read(&n);
	read(&k);
	if (n == 8) {
		write(178956970ll * k * (k - 1) * (k - 2) + k * (k - 1));
	}
	else{
		write((((cnt[n] - (ava2[n] << 1ll)) * k * (k - 1) * (k - 2)) >> 1ll) + ava2[n] * k * (k - 1));
	}
}
