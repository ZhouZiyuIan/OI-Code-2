#ifndef __WIN32
#include <stdio.h>
#endif
#include <string.h>
#define scanf __builtin_scanf
#define printf __builtin_printf
int n, a[200001];
long long f[200001][3][2][2];
long long max(const long long a, const long long b) {
	return a > b ? a : b;
}
void chk_max(long long *x, const long long y) {
	if (*x < y) {
		*x = y;
	}
}
int main() {
#ifndef __WIN32
	freopen("hero.in", "r", stdin);
	freopen("hero.out", "w", stdout);
#endif
	scanf("%d", &n);
	for (long long i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
	}
	if (n == 1) {
		printf("%d", a[1]);
		return 0;
	}
	memset(f, -0x3f, sizeof(f));
	f[1][2][0][0] = -a[1];
	f[1][1][1][0] = a[1];
	for (int i = 1; i < n; ++i) {
		for (int j = 0; j <= 2; ++j) {
			for (int k = 0; k <= 1; ++k) {
				for (int l = 0; l <= 1; ++l) {
					chk_max(&f[i + 1][(j + 2) % 3][0][l | (k == 0)], f[i][j][k][l] - a[i + 1]);
					chk_max(&f[i + 1][(j + 1) % 3][1][l | (k == 1)], f[i][j][k][l] + a[i + 1]);
				}
			}
		}
	}
	printf("%lld", max(f[n][1][0][1], f[n][1][1][1]));
}