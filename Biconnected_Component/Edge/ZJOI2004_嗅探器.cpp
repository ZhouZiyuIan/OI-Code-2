//
// Created by 118 on 25-7-28.
//
#pragma GCC optimize(3, "Ofast")
#include <stdio.h>
#include <string.h>
int n, a, b, x, y, k, ans = 1000000000, dfn[200001], low[200001], head[200001], to[400001], nxt[400001], cnt = 0;
void add(int u, int v) {
	to[cnt] = v;
	nxt[cnt] = head[u];
	head[u] = cnt++;
}
void tarjan(int u) {
	dfn[u] = low[u] = ++k;
	for (int i = head[u]; i != -1; i = nxt[i]) {
		int v = to[i];
		if (!dfn[v]) {
			tarjan(v);
			if (low[u] > low[v]) {
				low[u] = low[v];
			}
			if (u != a && dfn[b] >= dfn[v] && low[v] >= dfn[u] && u < ans) {
				ans = u;
			}
		}
		else if (low[u] > dfn[v]) {
			low[u] = dfn[v];
		}
	}
}
int main() {
	scanf("%d", &n);
	memset(head, -1, sizeof(head));
	while (scanf("%d%d", &x, &y) && (x || y)) {
		add(x, y);
		add(y, x);
	}
	scanf("%d%d", &a, &b);
	tarjan(a);
	if (ans == 1000000000) {
		printf("No solution\n");
	}
	else {
		printf("%d\n", ans);
	}
}
