//
// Created by 118 on 25-10-11.
//
#include<bits/stdc++.h>
using namespace std;
#define p 1000000007
int t, n, m, k, fac[400001], inv[400001], f[200001], s[2][200002];

int qp(int a, int b) {
	int res = 1;
	for (; b; b >>= 1) {
		if (b & 1)
			res = 1ll * res * a % p;
		a = 1ll * a * a % p;
	}
	return res;
}

int qsum(int x, int y) {
	if ((x += y) >= p)
		x -= p;
	if (x < 0)
		x += p;
	return x;
}

signed main() {
	freopen("splay.in", "r",stdin);
	freopen("splay.out", "w",stdout);
	for (int i = fac[0] = 1; i <= 400000; i++)
		fac[i] = 1ll * fac[i - 1] * i % p;
	inv[400000] = qp(fac[400000],p - 2);
	for (int i = 400000; i; i--)
		inv[i - 1] = 1ll * inv[i] * i % p;
	scanf("%d", &t);
	while (t--) {
		scanf("%d%d%d", &n, &m, &k);
		if (n == 1) {
			puts("0");
			continue;
		}
		if (k == 1) {
			printf("%d\n", qsum(qp(m + 1, n), -1ll * fac[m + n] * inv[m] % p * inv[n] % p));
			continue;
		}
		for (int i = 0; i <= m; i++)
			s[1][i] = m - i + 1;
		for (int i = 2, pw = m; i <= n; i++) {
			s[i & 1][(pw /= k) + 1] = 0;
			for (int j = pw; ~j; j--)
				s[i & 1][j] = qsum(s[i - 1 & 1][j * k], s[i & 1][j + 1]);
		}
		printf("%d\n", qsum(qp(m + 1, n), -s[n & 1][0]));
	}
	return 0;
}