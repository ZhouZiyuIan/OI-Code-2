#include <stdio.h>
#include <queue>
#include <string.h>
typedef long long ll;
using namespace std;
ll T, n, a[100001], b[100001], fa[100001], del[100001];
vector<ll> g[100001];
struct node {
	ll a, b, id;
};
priority_queue<node> q;
bool operator < (const node &x, const node &y) {
	if (x.a < x.b && y.a >= y.b) {
		return false;
	}
	if (x.a >= x.b && y.a < y.b) {
		return true;
	}
	if (x.a < x.b) {
		return x.a > y.a;
	}
	return x.b < y.b;
}
void dfs(const ll u, const ll f) {
	fa[u] = f;
	for (ll i = 0; i < g[u].size(); i++) {
		const ll v = g[u][i];
		if (v == f) {
			continue;
		}
		dfs(v, u);
	}
}
ll find(const ll x) {
	if (del[fa[x]]) {
		return fa[x] = find(fa[x]);
	}
	return fa[x];
}
signed main() {
	scanf("%lld", &T);
	while (T--) {
		for (ll i = 0; i<= 100000 ; i++) {
			g[i].clear();
			a[i]=0;
			b[i]=0;
			fa[i]=0;
			del[i]=0;
		}
		scanf("%lld", &n);
		for (ll i = 2; i <= n; i++) {
			scanf("%lld%lld", &a[i], &b[i]);
			q.emplace((node){a[i], b[i], i});
		}
		for (ll i = 1, x, y; i < n; i++) {
			scanf("%lld%lld", &x, &y);
			g[x].emplace_back(y);
			g[y].emplace_back(x);
		}
		dfs(1, 0);
		while (!q.empty()) {
			const node u = q.top();
			q.pop();
			if (del[u.id] || u.a != a[u.id] || u.b != b[u.id]) {
				continue;
			}
			const ll res = find(u.id);
			del[u.id] = 1;
			const ll A = max(a[res], a[u.id] + a[res] - b[res]), B = b[res] + b[u.id] - a[res] - a[u.id] + A;
			a[res] = A;
			b[res] = B;
			if (res > 1) {
				q.emplace((node){a[res], b[res], res});
			}
		}
		printf("%lld", a[1]);
	}
}