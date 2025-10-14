//
// Created by 118 on 25-9-15.
//
#ifndef FKZ
#include <stdio.h>
#endif
#define scanf __builtin_scanf
#define printf __builtin_printf
#define INF 1000000000
#define MOD 1000000007
#define min(a, b) (((a) < (b)) ? (a) : (b))
#define max(a, b) (((a) > (b)) ? (a) : (b))
int n, p, a[100001], lst[100001], plst[100001];
long long dp[100001] = {1};
typedef struct {
	int lzy, min1, min2, mx;
	long long tot_w, swam;
} Node;
Node st[400001];
Node merge(const Node &L, const Node &R) {
	Node res;
	res.tot_w = (L.tot_w + R.tot_w) % MOD;
	if (L.min1 < R.min1) {
		res.min1 = L.min1;
		res.swam = L.swam;
		res.min2 = min(L.min2, R.min1);
	}
	else if (R.min1 < L.min1) {
		res.min1 = R.min1;
		res.swam = R.swam;
		res.min2 = min(L.min1, R.min2);
	}
	else {
		res.min1 = L.min1;
		res.swam = (L.swam + R.swam) % MOD;
		res.min2 = min(L.min2, R.min2);
	}
	res.mx = max(L.mx, R.mx);
	res.lzy = 0;
	return res;
}
void add(const int k, const int add) {
	st[k].min1 += add;
	if (st[k].min2 < INF) {
		st[k].min2 += add;
	}
	st[k].mx += add;
	st[k].lzy += add;
}
void pushdown(const int k) {
	const int l = k << 1, r = l | 1;
	if (st[k].lzy) {
		add(l, st[k].lzy);
		add(r, st[k].lzy);
		st[k].lzy = 0;
	}
}
void build(const int k, const int l, const int r) {
	st[k].lzy = 0;
	if (l == r) {
		st[k].min1 = st[k].min2 = st[k].mx = INF;
		st[k].tot_w = st[k].swam = 0;
		return;
	}
	const int mid = (l + r) >> 1;
	build(k << 1, l, mid);
	build(k << 1 | 1, mid + 1, r);
	st[k] = merge(st[k << 1], st[k << 1 | 1]);
}
void modify(const int k, const int l, const int r, const int L, const int R, const int v) {
	if (L > r || R < l) {
		return;
	}
	if (L <= l && r <= R) {
		add(k, v);
		return;
	}
	pushdown(k);
	const int mid = (l + r) >> 1;
	modify(k << 1, l, mid, L, R, v);
	modify(k << 1 | 1, mid + 1, r, L, R, v);
	st[k] = merge(st[k << 1], st[k << 1 | 1]);
}
void update(const int p, const int l, const int r, const int pos, const long long w) {
	if (l == r) {
		st[p].mx = st[p].min1 = st[p].lzy = 0;
		st[p].min2 = INF;
		st[p].tot_w = (w % MOD + MOD) % MOD;
		st[p].swam = st[p].tot_w;
		return;
	}
	pushdown(p);
	const int mid = (l + r) >> 1;
	if (pos <= mid) {
		update(p << 1, l, mid, pos, w);
	}
	else {
		update((p << 1) | 1, mid + 1, r, pos, w);
	}
	st[p] = merge(st[p << 1], st[(p << 1) | 1]);
}
long long query(const int p, const int l, const int r, const int thr) {
	if (st[p].min1 > thr) {
		return 0;
	}
	if (st[p].mx <= thr || l == r) {
		return st[p].tot_w;
	}
	if (st[p].min2 > thr) {
		return st[p].swam;
	}
	pushdown(p);
	const int mid = (l + r) >> 1;
	long long res = 0;
	res += query(p << 1, l, mid, thr);
	res %= MOD;
	res += query((p << 1) | 1, mid + 1, r, thr);
	res %= MOD;
	return res;
}
int main() {
#ifndef FKZ
	freopen("home.in", "r", stdin);
	freopen("home.out", "w", stdout);
#endif
	scanf("%d%d", &n, &p);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &a[i]);
	}
	build(1, 1, n);
	dp[0] = 1;
	for (int i = 1; i <= n; ++i) {
		update(1, 1, n, i, dp[i - 1]);
		const int x = a[i], p1 = lst[x], p2 = plst[x];
		if (p1 + 1 <= i) {
			modify(1, 1, n, p1 + 1, i, 1);
		}
		if (p2 + 1 <= p1) {
			modify(1, 1, n, p2 + 1, p1, -1);
		}
		plst[x] = p1;
		lst[x] = i;
		dp[i] = query(1, 1, n, p);
		dp[i] %= MOD;
	}
	printf("%lld", dp[n]);
}
