#define scanf __builtin_scanf
#define printf __builtin_printf
int n, q, u, v, head[10000001], to[20000001], nxt[20000001], cnt, num[20000001], edge[10000001], par[10000001], dep[10000001], fa[10000001], lbl[10000001], sz[10000001], U[10000001], V[10000001], ans[10000001];
void add(const int u, const int v, const int no) {
	to[++cnt] = v;
	nxt[cnt] = head[u];
	num[cnt] = no;
	head[u] = cnt;
}
void dfs(const int x, const int fa) {
	par[x] = fa;
	dep[x] = dep[fa] + 1;
	for (int i = head[x]; i; i = nxt[i]) {
		if (to[i] == fa) {
			continue;
		}
		edge[to[i]] = num[i];
		dfs(to[i], x);
	}
}
int find(const int x) {
	if (fa[x] == -1) {
		return x;
	}
	return fa[x] = find(fa[x]);
}
int merge(int u, int v) {
	u = find(u);
	v = find(v);
	if (u == v) {
		return lbl[u];
	}
	if (sz[u] < sz[v]) {
		const int tmp = u;
		u = v;
		v = tmp;
	}
	sz[u] += sz[v];
	fa[v] = u;
	if (dep[lbl[u]] > dep[lbl[v]]) {
		lbl[u] = lbl[v];
	}
	return lbl[u];
}
int main() {
	scanf("%d%d", &n, &q);
	for (int i = 1; i ^ n; ++i) {
		scanf("%d%d", &u, &v);
		--u;
		--v;
		add(u, v, i);
		add(v, u, i);
	}
	dfs(0, 0);
	for (int i = 0; i ^ n; ++i) {
		fa[i] = -1;
		sz[i] = 1;
		lbl[i] = i;
	}
	for (int i = 0; i ^ q; ++i) {
		scanf("%d%d", &U[i], &V[i]);
		--U[i];
		--V[i];
	}
	for (int i = q - 1; i >= 0; --i) {
		U[i] = lbl[find(U[i])];
		V[i] = lbl[find(V[i])];
		while (U[i] != V[i]) {
			if (dep[U[i]] < dep[V[i]]) {
				const int tmp = U[i];
				U[i] = V[i];
				V[i] = tmp;
			}
			ans[edge[U[i]]] = i + 1;
			U[i] = merge(U[i], par[U[i]]);
		}
	}
	for (int i = 1; i ^ n; ++i) {
		printf("%d ", ans[i]);
	}
}
