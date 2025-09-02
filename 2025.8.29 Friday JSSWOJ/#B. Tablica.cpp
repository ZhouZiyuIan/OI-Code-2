#include <stdio.h>
#include <stdlib.h>
const int MOD = 1e9 + 7, inv2 = 5e8 + 4;
int n, m, t = 6000, C[6001][6001], pw[6001], pw2[6001], frac[6001];
long long ans = 0;
int min(int a, int b) {
	return a < b ? a : b;
}
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 0; i <= t; ++i) {
		C[i][0] = 1;
		for (int j = 1; j <= i; ++j) {
			C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % MOD;
		}
	}
	pw[0] = pw2[0] = frac[0] = 1;
	for (int i = 1; i <= t; ++i) {
		frac[i] = (long long)frac[i - 1] * i % MOD;
		pw2[i] = (long long)pw2[i - 1] * 2 % MOD;
		pw[i] = (long long)pw[i - 1] * inv2 % MOD;
	}
	for (int i = 0; i <= n; ++i) {
		int ch = i, cl = n + i - m;
		if (cl < 0 || cl > m) {
			continue;
		}
		long long mul = 0;
		int min_j = min(ch, cl);
		for (int j = 0; j <= min_j; ++j) {
			long long tmp = (long long)C[ch][j] * C[cl][j] % MOD;
			tmp = tmp * frac[n + i - 2 * j] % MOD;
			tmp = tmp * frac[j] % MOD;
			tmp = tmp * pw2[j] % MOD;
			tmp = tmp * (1 - 2 * (j % 2)) % MOD;
			mul = (mul + tmp) % MOD;
		}
		mul = mul * pw[ch + cl] % MOD;
		long long tmp = (long long)C[n][ch] * C[m][cl] % MOD;
		tmp = tmp * mul % MOD;
		ans = (ans + tmp) % MOD;
	}
	ans = (ans % MOD + MOD) % MOD;
	printf("%lld\n", ans);
}