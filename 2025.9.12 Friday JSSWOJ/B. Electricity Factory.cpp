//
// Created by 118 on 25-9-12.
//
#ifndef _WIN32
#include <cstdio>
#pragma GCC optimize(3, "Ofast", "unroll-loops")
#endif
#define scanf __builtin_scanf
#define printf __builtin_printf
int max(const int a, const int b) {
	return a > b ? a : b;
}
int n, m, H, c, h[11], p[11], g[11], e[11], dp[41][101][101][41], max_cp, flag;
void dfs(int x, int gr, int sy, int cp) {
	max_cp = max(max_cp, cp);
	if (x == m) {
		return;
	}
	for (int i = 0; i < n; ++i) {
		if (gr + h[i] >= 0 && sy + g[i] >= 0 && cp + e[i] >= 0 && dp[x][gr][sy][cp] + p[i] >= 0) {
			dp[x + 1][gr + h[i]][sy + g[i]][cp + e[i]] = max(dp[x + 1][gr + h[i]][sy + g[i]][cp + e[i]], dp[x][gr][sy][cp] + p[i]);
			dfs(x + 1, gr + h[i], sy + g[i], cp + e[i]);
		}
	}
}
int main() {
#ifndef _WIN32
	freopen("grid.in", "r", stdin);
	freopen("grid.out", "w", stdout);
#endif
	scanf("%d%d%d%d", &n, &m, &H, &c);
	for (int i = 0; i < n; ++i) {
		scanf("%d%d%d%d", &h[i],  &p[i], &g[i], &e[i]);
	}
	dfs(0, H, 0, 0);
	printf("%d\n", max_cp);
}

