#include <stdio.h>
int n, m, a[2002][1002], now, vis[2002];
char s[1002];
int gauss() {
	int ret = 0;
	for (int i = 1; i <= n; i++) {
		int tmp = i;
		while (!a[tmp][i] && tmp <= n) {
			++tmp;
		}
		if (tmp == n + 1) {
			++ret;
			continue;
		}
		vis[i] = 1;
		if (i != tmp) {
			for (int j = i; j <= n + 1; ++j) {
				const int temp = a[i][j];
				a[i][j] = a[tmp][j];
				a[tmp][j] = temp;
			}
		}
		for (int j = i + 1; j <= n; ++j) {
			if (!vis[j] && a[j][i]) {
				for (int k = i; k <= n + 1; k++) {
					a[j][k] ^= a[i][k];
				}
			}
		}
	}
	return ret;
}
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; ++i) {
		scanf("%s%d", s + 1, &a[i][n + 1]);
		for (int j = 1; j <= n; ++j) {
			a[i][j] = s[j] ^ 48;
		}
	}
	now = n;
	while (gauss()) {
		for (int i = 1; i <= n; ++i) {
			if (!vis[i]) {
				++now;
				if (now > m) {
					printf("Cannot Determine\n");
					return 0;
				}
				for (int j = 0; j <= n + 1; ++j) {
					a[now][j] = a[now][j] ^ a[i][j];
					a[i][j] = a[now][j] ^ a[i][j];
					a[now][j] = a[now][j] ^ a[i][j];
				}
			}
		}
	}
	for (int i = n; i >= 1; --i) {
		for (int j = i - 1; j >= 1; --j) {
			if (a[j][i]) {
				a[j][n + 1] ^= a[i][n + 1];
			}
		}
	}
	printf("%d\n", now);
	for (int i = 1; i <= n; ++i) {
		if(a[i][n + 1]) {
			printf("?y7M#");
		}
		else {
			printf("Earth");
		}
		putchar(10);
	}
}
