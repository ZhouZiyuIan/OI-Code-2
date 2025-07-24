//
// Created by 118 on 25-7-24.
//
#include<stdio.h>
int n, m, i, a, b, cnt, head[2000001], dfn[2000001], low[2000001], vis[2000001], dfncnt, sccsum, scc[2000001], stk[2000001], top;
struct edg {
	int v, nxt;
} e[2000001];
void add(int from, int to) {
	e[++cnt].nxt = head[from];
	head[from] = cnt;
	e[cnt].v = to;
}
void tarjan(int u) {
	vis[u] = 1;
	stk[++top] = u;
	dfn[u] = low[u] = ++dfncnt;
	for (int i = head[u]; i; i = e[i].nxt) {
		int v = e[i].v;
		if (!dfn[v]) {
			tarjan(v);
			low[u] = low[u] < low[v] ? low[u] : low[v];
		} else if (vis[v])low[u] = low[u] < dfn[v] ? low[u] : dfn[v];
	}
	if (dfn[u] == low[u]) {
		sccsum++;
		while (stk[top] != u) {
			scc[stk[top]] = sccsum;
			vis[stk[top--]] = 0;
		}
		scc[stk[top]] = sccsum;
		vis[stk[top--]] = 0;
	}
}
int main() {
	scanf("%d%d", &n, &m);
	while (m--) {
		scanf("%d%d", &a, &b);
		add(a, ((b & 1) ? b + 1 : b - 1));
		add(b, ((a & 1) ? a + 1 : a - 1));
	}
	n <<= 1;
	for (i = 1; i <= n; i++) {
		if (!dfn[i]) {
			tarjan(i);
		}
	}
	for (i = 1; i <= n; i++) {
		if ((i & 1) && (scc[i] == scc[i + 1])) {
			putchar('N');
			putchar('I');
			putchar('E');
			return 0;
		}
	}
	for (i = 1; i <= n; i++) {
		if (scc[i] < scc[((i & 1) ? i + 1 : i - 1)]) {
			printf("%d", i);
			putchar(10);
		}
	}
}
//怎么又是把今年 4 月写的 2-SAT 改了交的