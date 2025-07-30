//
// Created by 118 on 25-7-29.
//
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
typedef struct {
	double x, y;
} pt;
typedef struct {
	double l, r;
} seg;
seg S[505];
pt s, o;
int n;
double r, L, R;
double mpz(double a) {
	return a * a;
}
double dis(pt A, pt B) {
	return sqrt(mpz(A.x - B.x) + mpz(A.y - B.y));
}
int cmp(const void *a, const void *b) {
	return ((seg *) a) -> l < ((seg *) b) -> l ? -1 : 1;
}
int main() {
	while (scanf("%d", &n) && n) {
		scanf("%lf%lf", &s.x, &s.y);
		for (int i = 1; i <= n; i++) {
			scanf("%lf%lf%lf", &o.x, &o.y, &r);
			S[i].l = s.x - s.y * tan(asin(r / dis(s, o)) + asin((s.x - o.x) / dis(s, o)));
			S[i].r = s.x - s.y * tan(asin((s.x - o.x) / dis(s, o)) - asin(r / dis(s, o)));
			if (S[i].l > S[i].r) {
				double t = S[i].l;
				S[i].l = S[i].r;
				S[i].r = t;
			}
		}
		qsort(S + 1, n, sizeof(seg), cmp);
		L = S[1].l;
		R = S[1].r;
		for (int i = 2; i <= n; i++) {
			if (S[i].l > R) {
				printf("%.2f %.2f\n", L, R);
				L = S[i].l;
				R = S[i].r;
			}
			else {
				R = fmax(R, S[i].r);
			}
		}
		printf("%.2f %.2f\n\n", L, R);
	}
}