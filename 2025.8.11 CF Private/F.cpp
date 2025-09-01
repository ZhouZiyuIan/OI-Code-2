//
// Created by 118 on 25-8-1.
//
#include <algorithm>
#include <set>
#include <array>
#include <stdio.h>
using namespace std;
typedef long long ll;
int n, m, a[200001];
ll l[200001], r[200001];
void get(ll *l) {
	set<array<ll, 2> > st;
	for (int i = 1; i <= n; ++i) {
		l[i] = l[i - 1];
		array<ll, 2> p({a[i], a[i] + m - 1});
		auto it = st.upper_bound(p);
		if (it != st.begin() && prev(it)->at(1) >= p[0]) {
			it--;
			l[i] += it->at(1) + 1 - p[0];
			p = {it->at(0), it->at(1) + m};
			st.erase(it);
		}
		while (1) {
			it = st.upper_bound(p);
			if (it == st.end() || it->at(0) > p[1]) {
				break;
			}
			l[i] += (it->at(1) - it->at(0) + 1) / m * (p[1] + 1 - it->at(0));
			p[1] += it->at(1) - it->at(0) + 1;
			st.erase(it);
		}
		st.insert(p);
	}
}
void solve() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &a[i]);
	}
	get(l);
	reverse(a + 1, a + n + 1);
	get(r);
	ll ret = 9e18;
	for (int i = 1; i < n; ++i) {
		ret = min(ret, l[i] + r[n - i]);
	}
	printf("%lld\n", ret);
}
int T;
int main() {
	scanf("%d", &T);
	while (T--) {
		solve();
	}
}