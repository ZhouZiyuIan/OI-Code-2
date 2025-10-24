#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef __cplusplus
#define bool _Bool
#define true 1
#define false 0
#endif
const int MOD = 998244353;
int n, pc, fpr = 1, fcr = 1;
long long ans, res_c;
int main() {
	freopen("fibonacci.in", "r", stdin);
	freopen("fibonacci.out", "w", stdout);
	scanf("%d", &n);
	int *mu = (int *) malloc((n + 1) * sizeof(int)), mxp = n / 10 + 10, *pri = (int *) malloc(mxp * sizeof(int)), *preF = (int *) malloc((n + 1) * sizeof(int));
	bool *vis = (bool *) calloc((n + 1), sizeof(bool));
	if (!mu || !vis || !pri || !preF) {
		fprintf(stderr, "How to get 1 pt\n");
		return 1;
	}
	memset(mu, 0, (n + 1) * sizeof(int));
	if (n >= 1) {
		mu[1] = 1;
	}
	for (int i = 2; i <= n; ++i) {
		if (!vis[i]) {
			if (pc >= mxp) {
				int nmx = mxp << 1, *tmp = (int *) realloc(pri, nmx * sizeof(int));
				if (!tmp) {
					fprintf(stderr, "No 99pts Yes 100pts\n");
					return 1;
				}
				pri = tmp;
				mxp = nmx;
			}
			pri[pc++] = i;
			mu[i] = -1;
		}
		for (int j = 0; j < pc; ++j) {
			const long long v = 1LL * pri[j] * i;
			if (v > n) {
				break;
			}
			vis[v] = true;
			if (i % pri[j] == 0) {
				mu[v] = 0;
				break;
			}
			mu[v] = -mu[i];
		}
	}
	mu[0] = 0;
	for (int i = 1; i <= n; ++i) {
		mu[i] += mu[i - 1];
	}
	for (int i = 0; i <= n; ++i) {
		preF[i] = 0;
	}
	if (n >= 1) {
		preF[1] = 1 % MOD;
	}
	if (n >= 2) {
		preF[2] = 2 % MOD;
	}
	for (int i = 3; i <= n; ++i) {
		int fnx = fpr + fcr;
		if (fnx >= MOD) {
			fnx -= MOD;
		}
		preF[i] = preF[i - 1] + fnx;
		if (preF[i] >= MOD) {
			preF[i] -= MOD;
		}
		fpr = fcr;
		fcr = fnx;
	}
	if (n == 1) {
		preF[1] = 1 % MOD;
	}
	if (n == 0) {
		preF[0] = 0;
	}
	int l = 1;
	while (l <= n) {
		const int k = n / l, r = n / k;
		int sumF = preF[r];
		if (l > 1) {
			sumF -= preF[l - 1];
			if (sumF < 0) {
				sumF += MOD;
			}
		}
		res_c = 0;
		int p = 1;
		while (p <= k) {
			const int q = k / p, r2 = k / q, cnt = mu[r2] - mu[p - 1];
			__int128 prod = (__int128) cnt * q * q;
			long long add = (long long) (prod % MOD);
			if (add < 0) {
				add += MOD;
			}
			res_c += add;
			if (res_c >= MOD) {
				res_c -= MOD;
			}
			p = r2 + 1;
		}
		const int c = (int) (res_c % MOD);
		ans += (long long) sumF * c % MOD;
		if (ans >= MOD) {
			ans -= MOD;
		}
		l = r + 1;
	}
	printf("%d\n", (int) ((ans % MOD + MOD) % MOD));
	free(mu);
	free(vis);
	free(pri);
	free(preF);
}