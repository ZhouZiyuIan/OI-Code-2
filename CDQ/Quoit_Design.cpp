//
// Created by 118 on 25-7-29.
//
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
typedef struct {
	double x, y;
}pt;
pt p[100001], t[100001];
int cmp(const void *a, const void *b) {
	pt *p1 = (pt *)a;
	pt *p2 = (pt *)b;
	if (p1 -> x == p2 -> x) {
		return p1 -> y - p2 -> y >= 0 ? 1 : -1;
	}
	return p1 -> x - p2 -> x >= 0 ? 1 : -1;
}
double dis(pt a, pt b) {
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}
int n;
double bs = 0x3f3f3f3f;
int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; ++i) {
		scanf("%lf%lf", &p[i].x, &p[i].y);
	}
	qsort(p, n, sizeof(pt), cmp);
	for (int i = 0; i < n; ++i) {
		for (int j = i + 1; j <= i + 5 && j < n; ++j) {
			bs = fmin(bs, dis(p[i], p[j]));
		}
	}
	printf("%.2lf", bs / 2);
}