//
// Created by 118 on 25-9-1.
//
#include <stdio.h>
typedef long long ll;
int n, q, p[200001], op, x, y;
ll st[200001][9];
ll abs(const ll x) {
	return x < 0 ? -x : x;
}
int max(const int a, const int b) {
	return a > b ? a : b;
}
ll dfs(int x, int y) {
	if (y <= 8) {
		return st[x][y];
	}
	return abs(dfs(x, y - 1) - dfs(x + (1 << y - 1), y - 1));
}
int main() {
	scanf("%d%d", &n, &q);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &p[i]);
		st[i][0] = p[i];
	}
	for (int j = 1; j <= 8; ++j) {
		for (int i = 1; i + (1 << j) - 1 <= n; ++i) {
			st[i][j] = abs(st[i][j - 1] - st[i + (1 << j - 1)][j - 1]);
		}
	}
	for (int i = 1; i <= q; ++i) {
		scanf("%d%d%d", &op, &x, &y);
		if (op & 1) {
			st[x][0] = y;
			p[x] = ((int)(st[x][0]));
			for (int j = 1; j <= 8; ++j) {
				for (int k = max(x - 256, 1); k + (1 << j) - 1 <= n && k <= x; ++k) {
					st[k][j] = abs(st[k][j - 1] - st[k + (1 << j - 1)][j - 1]);
				}
			}
		}
		else {
			printf("%lld\n", dfs(x, y));
		}
	}
}