//
// Created by 118 on 25-8-1.
//
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll INF = 1e18;
struct Edge {
	int to;
	ll w;
};
struct DSU {
	vector<int> fa;
	DSU(int n) : fa(n) { iota(fa.begin(), fa.end(), 0); }
	int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }
	bool unite(int x, int y) {
		x = find(x), y = find(y);
		if (x == y) return false;
		fa[y] = x;
		return true;
	}
};
int T, n, m, k, x, y, a[500001], cnt;
ll w, ans;
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> T;
	while (T--) {
		cin >> n >> m >> k;
		vector<vector<Edge>> g(n + 1);
		for (int i = 0; i < m; ++i) {
			cin >> x >> y >> w;
			g[x].push_back({y, w});
			g[y].push_back({x, w});
		}
		for (int i = 0; i < k; ++i) {
			cin >> a[i];
		}
		vector<ll> dist(n + 1, INF);
		vector<int> from(n + 1, -1);
		priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<>> pq;
		for (int i = 0; i < k; ++i) {
			dist[a[i]] = 0;
			from[a[i]] = i;
			pq.emplace(0, a[i]);
		}
		while (!pq.empty()) {
			long long d = pq.top().first;
			int u = pq.top().second;
			pq.pop();
			if (d > dist[u]) {
				continue;
			}
			for (auto &e : g[u]) {
				if (dist[e.to] > dist[u] + e.w) {
					dist[e.to] = dist[u] + e.w;
					from[e.to] = from[u];
					pq.emplace(dist[e.to], e.to);
				}
			}
		}
		vector<tuple<ll, int, int>> edges;
		for (int u = 1; u <= n; ++u) {
			for (auto &e : g[u]) {
				int fu = from[u], fv = from[e.to];
				if (fu != fv && fu != -1 && fv != -1) {
					edges.emplace_back(dist[u] + e.w + dist[e.to], fu, fv);
				}
			}
		}
		ans = cnt = 0;
		sort(edges.begin(), edges.end());
		DSU dsu(k);
		for (auto &[w, u, v] : edges) {
			if (dsu.unite(u, v)) {
				ans += w;
				if (++cnt == k - 1) {
					break;
				}
			}
		}
		cout << ans << '\n';
	}
}