//
// Created by 118 on 25-9-26.
//
//#ifndef __WIN32
#include <stdio.h>
//#endif
#define scanf __builtin_scanf
#define printf __builtin_printf
typedef long long ll;
int N, M, head[100001], to[200001], nxt[200001], w[200001], cnt, fa[100001], dep[100001], sz[100001], son[100001], top[100001], dfn[100001], rnk[100001], dfst;
ll tots;
void add(int u, int v, int ww) {
	to[++cnt] = v;
	w[cnt] = ww;
	nxt[cnt] = head[u];
	head[u] = cnt;
	to[++cnt] = u;
	w[cnt] = ww;
	nxt[cnt] = head[v];
	head[v] = cnt;
}
void dfs1(int u, int f) {
	fa[u] = f;
	dep[u] = dep[f] + 1;
	sz[u] = 1;
	int maxsz = -1;
	for (int i = head[u]; i; i = nxt[i]) {
		const int v = to[i];
		if (v == f) {
			continue;
		}
		dfs1(v, u);
		sz[u] += sz[v];
		if (sz[v] > maxsz) {
			maxsz = sz[v];
			son[u] = v;
		}
	}
}
void dfs2(int u, int tp) {
	top[u] = tp;
	dfn[u] = ++dfst;
	rnk[dfst] = u;
	if (son[u]) {
		dfs2(son[u], tp);
	}
	for (int i = head[u]; i; i = nxt[i]) {
		int v = to[i];
		if (v != fa[u] && v != son[u]) {
			dfs2(v, v);
		}
	}
}
void dfs3(int u, int f) {
	for (int i = head[u]; i; i = nxt[i]) {
		int v = to[i];
		if (v == f) {
			continue;
		}
		tots += 1LL * w[i] * sz[v] * (N - sz[v]);
		dfs3(v, u);
	}
}
ll query(int u, int v, int x) {
	ll ret = 0;
	while (top[u] != top[v]) {
		if (dep[top[u]] < dep[top[v]]) {
			int tmp = u;
			u = v;
			v = tmp;
		}
		for (int i = dfn[top[u]]; i <= dfn[u]; ++i) {
			int node = rnk[i];
			ret += 1LL * x * sz[node] * (N - sz[node]);
		}
		u = fa[top[u]];
	}
	if (dep[u] > dep[v]) {
		int tmp = u;
		u = v;
		v = tmp;
	}
	for (int i = dfn[u] + 1; i <= dfn[v]; ++i) {
		int node = rnk[i];
		ret += 1LL * x * sz[node] * (N - sz[node]);
	}
	return ret;
}
int main() {
//#ifndef __WIN32
	freopen("heisenberg.in", "r", stdin);
	freopen("heisenberg.out", "w", stdout);
//#endif
	scanf("%d%d", &N, &M);
	for (int i = 1; i < N; ++i) {
		int u, v, ww;
		scanf("%d%d%d", &u, &v, &ww);
		add(u, v, ww);
	}
	dfs1(1, 0);
	dfs2(1, 1);
	dfs3(1, 0);
	while (M--) {
		int l, r, x;
		scanf("%d%d%d", &l, &r, &x);
		printf("%lld\n", tots - query(l, r, x));
	}
}
