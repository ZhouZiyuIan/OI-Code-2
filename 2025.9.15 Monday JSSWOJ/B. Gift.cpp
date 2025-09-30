//
// Created by 118 on 25-9-15.
//
#ifndef FKZ
#include <stdio.h>
#endif
#include <stdlib.h>
#define scanf __builtin_scanf
#define printf __builtin_printf
int n, m, T, q;
typedef struct {
	int v, w;
} Item;
Item items[500001];
int cmp(const void* a, const void* b) {
	const Item *x = (Item*)a, *y = (Item*)b;
	return x -> w > y -> w ? 1 : -1;
}
int chk(Item si[], const int si_sz, const int mid, const int q) {
	if (si_sz < q) {
		return 0;
	}
	Item big[n], sml[n];
	int big_sz = 0, sml_sz = 0;
	for (int i = 0; i < si_sz; ++i) {
		const Item item = si[i];
		if (item.v >= mid) {
			big[big_sz++] = item;
		}
		else {
			sml[sml_sz++] = item;
		}
	}
	const int nb = (q + 1) >> 1;
	if (big_sz < nb) {
		return 0;
	}
	qsort(big, big_sz, sizeof(Item), cmp);
	long long tc = 0;
	for (int i = 0; i < nb; i++) {
		tc += big[i].w;
	}
	const int rmn = q - nb;
	if (rmn > 0) {
		qsort(sml, sml_sz, sizeof(Item), cmp);
		for (int i = 0; i < rmn && i < sml_sz; ++i) {
			tc += sml[i].w;
		}
	}
	return tc <= m && rmn <= sml_sz;
}
int sol(const int q) {
	if (q > n || (q & 1) == 0) {
		return -1;
	}
	Item vi[n];
	int vi_sz = 0;
	for (int i = 0; i < n; ++i) {
		vi[vi_sz++] = items[i];
	}
	int l = 0, r = 1e6 + 1, ans = -1;
	while (l <= r) {
		const int mid = (l + r) >> 1;
		if (chk(vi, vi_sz, mid, q)) {
			ans = mid;
			l = mid + 1;
		}
		else {
			r = mid - 1;
		}
	}
	return ans;
}
int main() {
#ifndef FKZ
	freopen("gift.in", "r", stdin);
	freopen("gift.out", "w", stdout);
#endif
	scanf("%d%d%d", &n, &m, &T);
	for (int i = 0; i < n; ++i) {
		scanf("%d%d", &items[i].v, &items[i].w);
	}
	while (T--) {
		scanf("%d", &q);
		printf("%d\n", sol(q));
	}
}