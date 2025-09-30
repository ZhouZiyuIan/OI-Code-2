//
// Created by 118 on 25-9-15.
//
#pragma GCC optimize("Ofast","unroll-loops","fast-math","inline","no-stack-protector")
#ifndef FKZ
#include <stdio.h>
#endif
#include <string.h>
#define scanf __builtin_scanf
#define printf __builtin_printf
#define INF 1000000000
#define MOD 1000000007
#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))
static inline void addmod(long long &x, long long y){
	x += y;
	if (x >= MOD) x -= MOD;
}
int n, p, a[100001], lst[100001], plst[100001];
long long dp[100001] = {1};
typedef struct {
	int lzy, min1, min2, mx;
	long long tot_w, swam;
} Node;
Node st[400001];
static inline Node merge(const Node &L, const Node &R) {
	Node res;
	long long tw = L.tot_w + R.tot_w;
	if (tw >= MOD) tw -= MOD;
	res.tot_w = tw;
	if (L.min1 < R.min1) {
		res.min1 = L.min1;
		res.swam = L.swam;
		res.min2 = min(L.min2, R.min1);
	} else if (R.min1 < L.min1) {
		res.min1 = R.min1;
		res.swam = R.swam;
		res.min2 = min(L.min1, R.min2);
	} else {
		res.min1 = L.min1;
		long long sm = L.swam + R.swam;
		if (sm >= MOD) sm -= MOD;
		res.swam = sm;
		res.min2 = min(L.min2, R.min2);
	}
	res.mx = max(L.mx, R.mx);
	res.lzy = 0;
	return res;
}
static inline void add_tag(const int k, const int v) {
	st[k].min1 += v;
	if (st[k].min2 < INF) st[k].min2 += v;
	st[k].mx += v;
	st[k].lzy += v;
}
static inline void pushdown(const int k) {
	const int l = k << 1, r = l | 1;
	const int z = st[k].lzy;
	if (z) {
		add_tag(l, z);
		add_tag(r, z);
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
	if (L > r || R < l) return;
	if (L <= l && r <= R) {
		add_tag(k, v);
		return;
	}
	pushdown(k);
	const int mid = (l + r) >> 1;
	modify(k << 1, l, mid, L, R, v);
	modify(k << 1 | 1, mid + 1, r, L, R, v);
	st[k] = merge(st[k << 1], st[k << 1 | 1]);
}
void update(const int k, const int l, const int r, const int pos, const long long w) {
	if (l == r) {
		st[k].mx = st[k].min1 = 0;
		st[k].min2 = INF;
		st[k].lzy = 0;
		long long t = w % MOD;
		if (t < 0) t += MOD;
		st[k].tot_w = t;
		st[k].swam = t;
		return;
	}
	pushdown(k);
	const int mid = (l + r) >> 1;
	if (pos <= mid) update(k << 1, l, mid, pos, w);
	else update(k << 1 | 1, mid + 1, r, pos, w);
	st[k] = merge(st[k << 1], st[k << 1 | 1]);
}
long long query(const int k, const int l, const int r, const int thr) {
	if (st[k].min1 > thr) return 0;
	if (st[k].mx <= thr || l == r) return st[k].tot_w;
	if (st[k].min2 > thr) return st[k].swam;
	pushdown(k);
	const int mid = (l + r) >> 1;
	long long res = 0;
	res = query(k << 1, l, mid, thr);
	addmod(res, query(k << 1 | 1, mid + 1, r, thr));
	return res;
}
int main() {
#ifndef FKZ
	freopen("home.in", "r", stdin);
	freopen("home.out", "w", stdout);
#endif
	scanf("%d%d", &n, &p);
	for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
	if(p==1){
		static long long pre[100002];
		dp[0]=1; pre[0]=1;
		int last_diff=0;
		for(int i=1;i<=n;i++){
			if(i>1 && a[i]!=a[i-1]) last_diff=i-1;
			// 合法起点范围是 [last_diff+1, i]
			int L = last_diff+1;
			dp[i] = (pre[i-1] - pre[L-2] + MOD) % MOD;
			pre[i] = (pre[i-1] + dp[i]) % MOD;
		}
		printf("%lld\n",dp[n]%MOD);
		return 0;
	}


	build(1, 1, n);
	dp[0] = 1;
	for (int i = 1; i <= n; ++i) {
		update(1, 1, n, i, dp[i - 1]);
		const int x = a[i];
		const int p1 = lst[x];
		const int p2 = plst[x];
		if (p1 + 1 <= i) modify(1, 1, n, p1 + 1, i, +1);
		if (p2 + 1 <= p1) modify(1, 1, n, p2 + 1, p1, -1);
		plst[x] = p1;
		lst[x] = i;
		dp[i] = query(1, 1, n, p);
		if (dp[i] >= MOD) dp[i] -= MOD;
	}
	printf("%lld", dp[n] % MOD);
}

