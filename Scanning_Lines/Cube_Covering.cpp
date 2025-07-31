//
// Created by 118 on 25-7-30.
//
#include <stdio.h>
#include <stdlib.h>
int n, x, y, z, r, tot, area, sur[2001][2001], ans;
typedef struct {
	int x, y, a, b, h, tag;
}Diff;
Diff d[2001];
int cmp(const void *a, const void *b) {
	return ((Diff*)a)->h - ((Diff*)b)->h;
}
int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; ++i) {
		scanf("%d%d%d%d", &x, &y, &z, &r);
		x += 1000;
		y += 1000;
		z += 1000;
		d[++tot] = (Diff){x - r + 1, y - r + 1, x + r, y + r, z - r, 1};
		d[++tot] = (Diff){x - r + 1, y - r + 1, x + r, y + r, z + r, -1};
	}
	qsort(d + 1, tot, sizeof(Diff), cmp);
	for (int i = 1; i < tot; ++i) {
		for (int j = d[i].x; j <= d[i].a; ++j) {
			for (int k = d[i].y; k <= d[i].b; ++k) {
				sur[j][k] += d[i].tag;
				if (sur[j][k] == 1 && d[i].tag == 1) {
					++area;
				}
				if (sur[j][k] == 0 && d[i].tag == -1) {
					--area;
				}
			}
		}
		ans += area * (d[i + 1].h - d[i].h);
	}
	printf("%d", ans);
}