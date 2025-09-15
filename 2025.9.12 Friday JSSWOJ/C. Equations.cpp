//
// Created by 118 on 25-9-13.
//
#include <stdio.h>
long long T, c, n, m, a[100001], tree[400001], pos[400001], op, l, r, s;
long long gcd(const long long a, const long long b) {
	return b ? gcd(b, a % b) : a;
}
void pushup(const long long id) {
	tree[id] = gcd(tree[id << 1], tree[id << 1 | 1]);
}
void build(const long long k, const long long l, const long long r) {
	if (l == r) {
		pos[l] = k;
		tree[k] = a[l];
		return;
	}
	const long long mid = (l + r) >> 1;
	build(k << 1, l, mid);
	build(k << 1 | 1, mid + 1, r);
	pushup(k);
}
long long query(const long long L, const long long R, const long long l, const long long r, const long long cur) {
	if (L <= l && R >= r) {
		return tree[cur];
	}
	const long long mid = (l + r) >> 1;
	if (L <= mid && R > mid) {
		return gcd(query(L, R, l, mid, cur << 1), query(L, R, mid + 1, r, cur << 1 | 1));
	}
	if (L <= mid) {
		return query(L, R, l, mid, cur << 1);
	}
	return query(L, R, mid + 1, r, cur << 1 | 1);
}
void modify(long long k, const long long v) {
	k = pos[k];
	tree[k] = v;
	for (k >>= 1; k; k >>= 1) {
		pushup(k);
	}
}
int main() {
	freopen("equation.in", "r", stdin);
	freopen("equation.out", "w", stdout);
	scanf("%lld%lld", &T, &c);
	while (T--) {
		scanf("%lld%lld", &n, &m);
		for (long long i = 1; i <= n; ++i) {
			scanf("%lld", &a[i]);
		}
		build(1, 1, n);
		while (m--) {
			scanf("%lld%lld%lld", &op, &l, &r);
			if (op == 1) {
				modify(l, r);
			}
			else {
				scanf("%lld", &s);
				printf("%lld\n", s / query(l, r, 1, n, 1));
			}
		}
	}
}