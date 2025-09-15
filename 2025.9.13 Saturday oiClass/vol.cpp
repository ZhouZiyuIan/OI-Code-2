//
// Created by 118 on 25-9-13.
//
#include <vector>
#include <iostream>
#include <queue>
#include <unordered_map>
using namespace std;
int n, u, v, w, t, S;
int main() {
#ifndef FKZ
	freopen("string.in", "r", stdin);
	freopen("string.out", "w", stdout);
#endif
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n;
	vector<int> w(n + 1);
	for (int i = 1; i <= n; ++i) {
		cin >> w[i];
	}
	vector<vector<int> > g(n + 1);
	for (int i = 0; i < n - 1; ++i) {
		cin >> u >> v;
		g[u].emplace_back(v);
		g[v].emplace_back(u);
	}
	vector<int> dep(n + 1, -1);
	queue<int> q;
	dep[1] = 0;
	q.emplace(1);
	int mxDep = 0;
	while (!q.empty()) {
		const int u = q.front();
		q.pop();
		mxDep = max(mxDep, dep[u]);
		for (int v: g[u]) {
			if (dep[v] == -1) {
				dep[v] = dep[u] + 1;
				q.emplace(v);
			}
		}
	}
	int md = mxDep;
	if (n > 5000) md = min(md, 5000);
	vector<int> ans(n + 1, 0);
	for (int st = 1; st <= n; ++st) {
		if (dep[st] <= 0) {
			ans[st] = 0;
			continue;
		}
		if (1 + w[st] <= 0) {
			ans[st] = 0;
			continue;
		}
		unordered_map<long long, int> bs;
		auto kp = [](const int node, const int time)-> long long {
			return (static_cast<long long>(node) << 32) | static_cast<unsigned>(time);
		};
		int bm = 0;
		vector<tuple<int, int, int> > stk;
		stk.emplace_back(st, 0, 1 + w[st]);
		bs[kp(st, 0)] = 1 + w[st];
		while (!stk.empty()) {
			tie(u, t, S) = stk.back();
			stk.pop_back();
			bm = max(bm, t);
			if (t >= md) {
				continue;
			}
			for (int v: g[u]) {
				int nxt = t + 1;
				if (dep[v] <= nxt) {
					continue;
				}
				int nxS = S + w[v];
				if (nxS <= 0) {
					continue;
				}
				long long key = kp(v, nxt);
				auto it = bs.find(key);
				if (it != bs.end() && it->second >= nxS) {
					continue;
				}
				bs[key] = nxS;
				stk.emplace_back(v, nxt, nxS);
			}
		}
		ans[st] = bm;
	}
	for (int i = 1; i <= n; ++i) {
		cout << (ans[i] ? ans[i] + 1 : 0) << '\n';
	}
}