#include <stdio.h>
#include <stdlib.h>
typedef long long ll;
typedef struct {
	ll a, b;
} pr;
ll n, q, val[200001], dep[200001], pos[200001], d_cnt[200001], *adj[200001], a_cnt[200001], *ps[200001], u, k, v;
pr *dg[200001];
void dfs(ll u, ll p) {
	dep[u] = dep[p] + 1;
	for (ll i = 0; i < a_cnt[u]; ++i) {
		ll v = adj[u][i];
		if (v != p) dfs(v, u);
	}
}
int cmp(const void *x, const void *y) {
	const pr *p1 = (pr *) x, *p2 = (pr *) y;
	return (p2->a > p1->a) - (p2->a < p1->a);
}
int main() {
	freopen("6.in", "r", stdin);
	freopen("6.out", "w", stdout);
	scanf("%lld%lld", &n, &q);
	for (ll i = 1; i <= n; ++i) {
		scanf("%lld", &val[i]);
	}
	for (ll i = 1; i < n; ++i) {
		scanf("%lld%lld", &u, &v);
		a_cnt[u]++;
		a_cnt[v]++;
		adj[u] = (ll*)realloc(adj[u], a_cnt[u] * sizeof(ll));
		adj[v] = (ll*)realloc(adj[v], a_cnt[v] * sizeof(ll));
		adj[u][a_cnt[u] - 1] = v;
		adj[v][a_cnt[v] - 1] = u;
	}
	dfs(1, 0);
	for (ll i = 1; i <= n; ++i) {
		++d_cnt[dep[i]];
	}
	for (ll d = 1; d <= n; ++d) {
		if (d_cnt[d] > 0) {
			dg[d] = (pr*)malloc((d_cnt[d] + 1) * sizeof(pr));
			ps[d] = (ll*)malloc((d_cnt[d] + 1) * sizeof(ll));
			dg[d][0] = (pr){0, 0};
			ps[d][0] = 0;
			d_cnt[d] = 1;
		}
	}
	for (ll i = 1; i <= n; ++i) {
		dg[dep[i]][d_cnt[dep[i]]++] = (pr){val[i], i};
	}
	for (ll d = 1; d <= n; ++d) {
		if (d_cnt[d] > 1) {
			qsort(dg[d] + 1, d_cnt[d] - 1, sizeof(pr), cmp);
		}
	}
	for (ll d = 1; d <= n; ++d) {
		for (ll j = 1; j < d_cnt[d]; ++j) {
			pos[dg[d][j].b] = j;
		}
	}
	for (ll d = 1; d <= n; ++d) {
		for (ll j = 1; j < d_cnt[d]; ++j) {
			ll pre = ps[d][j - 1], sum = pre + dg[d][j].a;
			ps[d][j] = (pre > sum) ? pre : sum;
		}
	}
	while (q--) {
		scanf("%lld%lld", &u, &k);
		if (pos[u] <= k) {
			ll res = ps[dep[u]][k + 1] - (val[u] > 0 ? val[u] : 0);
			printf("%lld\n", res);
		}
		else {
			printf("%lld\n", ps[dep[u]][k]);
		}
	}
}
