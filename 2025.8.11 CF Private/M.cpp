//
// Created by 118 on 25-8-1.
//
#include <stdio.h>
const long long MOD = 1e9 + 7;
long long T, n, m, k, fac[1000001] = {1}, c1[1000001] = {1}, c2[1000001] = {1}, ans;
void init() {
	for (long long i = 1; i <= n; ++i) {
		c1[i] = c1[i - 1] * m % MOD;
		c2[i] = c2[i - 1] * (m - 1) % MOD;
	}
	ans = 0;
}
long long fstpow(long long a, long long b) {
	long long res = 1;
	while (b) {
		if (b & 1) {
			res = res * a % MOD;
		}
		a = a * a % MOD;
		b >>= 1;
	}
	return res;
}
long long C(long long a, long long b) {
	if (a < b) {
		return 0;
	}
	return fac[a] * fstpow(fac[b], MOD - 2) % MOD * fstpow(fac[a - b], MOD - 2) % MOD;
}
int main() {
	scanf("%lld", &T);
	for (long long i = 1; i <= 1000000; ++i) {
		fac[i] = fac[i - 1] * i % MOD;
	}
	while (T--) {
		scanf("%lld%lld%lld", &n, &m, &k);
		init();
		for (long long i = 1; i <= k; i++) {
			ans = (ans + c1[i] * c2[k - i] % MOD * C(n - k + 1, i) % MOD * C(k - 1, i - 1)) % MOD;
		}
		printf("%lld\n", ans);
	}
}