//
// Created by 118 on 25-9-26.
//
#ifndef FKZ
#include <stdio.h>
#endif
#define scanf __builtin_scanf
#define printf __builtin_printf
int n, m, a[1000001], tree[4000001], tag[4000001], x, y, z;
char op[1];
int gcd(const int a, const int b) {
	return b ? gcd(b, a % b) : a;
}
void build(const int k, const int l, const int r) {
	if (l == r) {
		tree[k] = a[l];
		return;
	}
	const int mid = (l + r) >> 1;
	build(k << 1, l, mid);
	build(k << 1 | 1, mid + 1, r);
	tree[k] = gcd(tree[k << 1], tree[k << 1 | 1]);
}
void pushdown(const int k) {
	tag[k << 1] = tag[k << 1 | 1] = tree[k << 1] = tree[k << 1 | 1] = tag[k];
	tag[k] = 0;
}
void modify(const int k, const int l, const int r, const int L, const int R, const int val) {
	if (L > r || R < l) {
		return;
	}
	if (L <= l && r <= R) {
		tag[k] = tree[k] = val;
		return;
	}
	if (tag[k]) {
		pushdown(k);
	}
	const int mid = (l + r) >> 1;
	modify(k << 1, l, mid, L, R, val);
	modify(k << 1 | 1, mid + 1, r, L, R, val);
	tree[k] = gcd(tree[k << 1], tree[k << 1 | 1]);
}
int query(const int k, const int l, const int r, const int L, const int R) {
	if (L > r || R < l) {
		return 0;
	}
	if (tag[k]) {
		pushdown(k);
	}
	if (l == r || (L <= l && r <= R)) {
		return tree[k];
	}
	const int mid = (l + r) >> 1;
	return gcd(query(k << 1, l, mid, L, R), query(k << 1 | 1, mid + 1, r, L, R));
}
int main() {
#ifndef FKZ
	freopen("whale.in", "r", stdin);
	freopen("whale.out", "w", stdout);
#endif
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &a[i]);
	}
	build(1, 1, n);
	while (m--) {
		scanf("%s%d%d", op, &x, &y);
		if (op[0] == 'S') {
			scanf("%d", &z);
			modify(1, 1, n, x, y, z);
		}
		else {
			printf("%d\n", query(1, 1, n, x, y));
		}
	}
}
