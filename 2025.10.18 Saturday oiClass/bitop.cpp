//
// Created by 118 on 25-10-18.
//
#include <stdio.h> // NOLINT(*-deprecated-headers)
#include <ctype.h> // NOLINT(*-deprecated-headers)
// ReSharper disable once CppUnusedIncludeDirective
#include <stdbool.h> // NOLINT(*-deprecated-headers)
#include <stdlib.h> // NOLINT(*-deprecated-headers)
#define FileIO(str) freopen(str".in", "r", stdin); freopen(str".out", "w", stdout)
#define MOD 1000000007
void read(int *w) {
	int f = 1, x = 0, s = getchar();
	while (!isdigit(s)) {
		if (s == 45) {
			f = -f;
		}
		s = getchar();
	}
	do {
		x = (x << 1) + (x << 3) + (s ^ 48);
		s = getchar();
	}
	while (isdigit(s));
	x *= f;
	*w = x;
}
void write(int x) {
	int len_s = 0, str[10];
	while (x > 9) {
		str[len_s++] = x % 10 ^ 48;
		x /= 10;
	}
	str[len_s] = x % 10 ^ 48;
	for (int i = len_s; i >= 0; --i) {
		putchar(str[i]);
	}
}
int min(const int a, const int b) {
	return a < b ? a : b;
}
int max(const int a, const int b) {
	return a > b ? a : b;
}
int abs(const int x) {
	return x < 0 ? -x : x;
}
int fstpow(int a, int b) {
	int res = 1;
	while (b) {
		if (b & 1) {
			res = res * a % MOD;
		}
		a = a * a % MOD;
		b >>= 1;
	}
	a %= MOD;
	return res;
}
int n, k, ch, len, yes, tot1, suff1[500001];
static bool s[500001], *best;
static bool* fun1() {
	const int b = k << 1;
	// ReSharper disable once CppCStyleCast
	// ReSharper disable once CppUseAuto
	bool* t = (bool *) malloc(n * sizeof(bool));
	int rem1 = tot1, used = 0;
	for (int i = 0; i < n; ++i) {
		bool flag = false;
		if (rem1 <= n - 1 - i) {
			const int tmp = s[i] ? 1 : 0, tmp1 = abs(suff1[i + 1] - rem1);
			// ReSharper disable once CppCStyleCast
			if ((long long) used + tmp + tmp1 <= b) {
				flag = true;
			}
		}
		if (flag) {
			// ReSharper disable once CppCStyleCast
			// ReSharper disable once CppZeroConstantCanBeReplacedWithNullptr
			t[i] = (bool*) false;
			if (s[i]) {
				++used;
			}
		}
		else {
			// ReSharper disable once CppCStyleCast
			t[i] = (bool*) true;
			if (!s[i]) {
				++used;
			}
			--rem1;
		}
	}
	return t;
}
int calc(const bool *s) {
	int res = 0;
	for (int i = 0; i < n; ++i) {
		// ReSharper disable twice CppCStyleCast
		// ReSharper disable once CppDFANullDereference
		res = (int)(((long long)res * 2 + s[i] ) % MOD);
	}
	return res;
}
int main() {
#ifndef __WIN32
	FileIO("bitop");
#endif
	read(&n);
	read(&k);
	best = (bool *) malloc(n * sizeof(bool));
	while (ch = getchar(), ch != 48 && ch != 49) {
	}
	do {
		tot1 += ch ^ 48;
		s[++len] = ch ^ 48;
		ch = getchar();
	} while (ch == 48 || ch == 49);
	for (int i = n - 1; i >= 0; --i) {
		suff1[i] = suff1[i + 1] + s[i];
	}
	best = fun1();
	write(calc(best));
}