//
// Created by 118 on 25-10-14.
//
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#define MOD 1000000007
#define FileIO(str) freopen(str".in", "r", stdin); freopen(str".out", "w", stdout)
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
	if (x < 0) {
		putchar(45);
		x = -x;
	}
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
typedef struct {
	int a, b, c, d;
} Mat;
Mat dp[2001][2001], f[2001], t;
int n, k, s, ans, cnt;
bool s2[2001];
Mat times(const Mat x, const Mat y) {
	return (Mat){
		(int)((1ll * x.a * y.a + 1ll * x.b * y.c) % MOD), (int)((1ll * x.a * y.b + 1ll * x.b * y.d) % MOD),
		(int)((1ll * x.c * y.a + 1ll * x.d * y.c) % MOD), (int)((1ll * x.c * y.b + 1ll * x.d * y.d) % MOD)
	};
}
Mat plus(const Mat x, const Mat y) {
	return (Mat){
		(x.a + y.a) % MOD, (x.b + y.b) % MOD,
		(x.c + y.c) % MOD, (x.d + y.d) % MOD
	};
}
int main() {
#ifndef __WIN32
	FileIO("b");
#endif
	read(&n);
	read(&k);
	t = dp[0][0] = (Mat) {1, 0, 0, 1};
	f[1] = (Mat) {1, 1, 1, 0};
	for (int i = 1; i <= n; ++i) {
		s = getchar() ^ 48;
		s2[i] = s;
	}
	for (int i = 1; i <= n; ++i) {
		if (i != 1) {
			f[i] = times(f[i - 1], f[i - 1]);
		}
		for (int j = 0; j <= min(i, k); ++j) {
			dp[i][j] = dp[i - 1][j];
			if (j > 0) {
				dp[i][j] = plus(dp[i][j], times(dp[i - 1][j - 1], f[i]));
			}
		}
	}
	for (int i = 1; i <= n; ++i) {
		if (s2[i]) {
			if (cnt <= k) {
				ans = (ans + times(t, dp[n - i][k - cnt]).a) % MOD;
			}
			t = times(t, f[n - i + 1]);
			++cnt;
		}
	}
	if (cnt == k) {
		ans = (ans + t.a) % MOD;
	}
	write(ans);
}
