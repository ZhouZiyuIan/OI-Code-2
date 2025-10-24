#include <ctype.h>
#include <stdio.h>
#define FileIO(str) freopen(str".in", "r", stdin); freopen(str".out", "w", stdout)
#define MOD 1000000007
void read(long long *w) {
	long long f = 1, x = 0, s = getchar();
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
void write(long long x) {
	long long len_s = 0;
	int str[10];
	while (x > 9) {
		// ReSharper disable once CppCStyleCast
		str[len_s++] = (int)(x % 10 ^ 48);
		x /= 10;
	}
	// ReSharper disable once CppCStyleCast
	str[len_s] = (int)(x % 10 ^ 48);
	for (long long i = len_s; i >= 0; --i) {
		putchar(str[i]);
	}
}
long long min(const long long a, const long long b) {
	return a < b ? a : b;
}
long long max(const long long a, const long long b) {
	return a > b ? a : b;
}
long long fstpow(long long a, long long b) {
	a %= MOD;
	long long res = 1;
	while (b) {
		if (b & 1) {
			// ReSharper disable CppFunctionalStyleCast
			res = 1ll * res * a % MOD;
			// ReSharper restore CppFunctionalStyleCast
		}
		a = a * a % MOD;
		b >>= 1;
	}
	return res;
}
long long n, k, a[200001], burn[200001], ans;
int main() {
	#ifndef __WIN32
	FileIO("fire");
	#endif
	read(&n);
	read(&k);
	a[0] = 1;
	for (long long i = 1; i <= n; ++i) {
		read(&a[i]);
		burn[i] = burn[i - 1];
		if (a[i] == 100) {
			++burn[i];
			a[i] = a[i - 1];
		}
		// ReSharper disable CppFunctionalStyleCast
		a[i] = 570000004ll * (100 - a[i]) % MOD * a[i - 1] % MOD;
		// ReSharper restore CppFunctionalStyleCast
	}
	for (long long i = 1; i <= n; ++i) {
		ans += 1ll - 1ll * a[min(i + k, n)] * fstpow(a[max(i - k - 1, 0)],MOD - 2) % MOD * fstpow(0, burn[min(i + k, n)] - burn[max(i - k - 1, 0)]) % MOD + MOD;
		ans %= MOD;
	}
	write(ans);
}