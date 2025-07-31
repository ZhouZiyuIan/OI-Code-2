//
// Created by 118 on 25-7-31.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int n, m, x, y, cnt, res[5001], ans[5001], deg[5001], vis[5001], gra[5001][5001], flag, u, v;
int cmp(const void *a, const void *b) {
	return *(int*)a - *(int*)b;
}
void dfs(int u) {
	vis[u] = 1;
	res[++cnt] = u;
	for (int i = 0; i < deg[u]; ++i) {
		int v = gra[u][i];
		if ((u == x && v == y) || (u == y && v == x)) {
			continue;
		}
		if (!vis[v]) {
			dfs(v);
		}
	}
}
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 0; i < m; ++i) {
		scanf("%d%d", &u, &v);
		gra[u][deg[u]++] = v;
		gra[v][deg[v]++] = u;
	}
	for (int i = 1; i <= n; ++i) {
		qsort(gra[i], deg[i], sizeof(int), cmp);
	}
	if (m == n - 1) {
		dfs(1);
		for (int i = 1; i <= n; i++) {
			printf("%d ", res[i]);
		}
	}
	else {
		memset(ans, 0, sizeof(ans));
		for (x = 1; x <= n; ++x) {
			for (int j = 0; j < deg[x]; ++j) {
				y = gra[x][j];
				if (y < x) {
					continue;
				}
				cnt = 0;
				memset(vis, 0, sizeof(vis));
				dfs(1);
				if (cnt != n) {
					continue;
				}
				flag = 0;
				for (int i = 1; i <= n; i++) {
					if (!ans[i] || res[i] < ans[i]) {
						flag = 1;
						break;
					}
					if (res[i] > ans[i]) {
						break;
					}
				}
				if (flag) {
					memcpy(ans, res, sizeof(res));
				}
			}
		}
		for (int i = 1; i <= n; ++i) {
			printf("%d ", ans[i]);
		}
	}
}