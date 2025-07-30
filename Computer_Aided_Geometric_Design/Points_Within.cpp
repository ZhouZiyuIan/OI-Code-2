//
// Created by 118 on 25-7-29.
//
#include <stdio.h>
#include <stdbool.h>
double fabs(double x) {
	return x >= 0 ? x : -x;
}
typedef struct {
	double x, y;
}point;
point pts[101], p;
const double eps = 1e-8;
int n, m;
int dblcmp(double d) {
	return fabs(d) < eps ? 0 : (d > 0 ? 1 : -1);
}
int xx(point p) {
	return dblcmp(p.x) >= 0 ? (dblcmp(p.y) >= 0 ? 0 : 3) : (dblcmp(p.y) >= 0 ? 1 : 2);
}
double Det(double x1, double y1, double x2, double y2) {
	return x1 * y2 - x2 * y1;
}
bool chk(point t[], point q) {
	for (int i = 0; i < n; ++i) {
		t[i].x -= q.x;
		t[i].y -= q.y;
	}
	int sum = 0, a1 = xx(t[0]), i;
	for (i = 0; i < n; ++i) {
		int k = (i + 1) % n;
		if (!dblcmp(t[k].x) && !dblcmp(t[k].y)) {
			break;
		}
		int detSign = dblcmp(Det(t[i].x, t[i].y, t[k].x, t[k].y));
		if (!detSign && dblcmp(t[i].x * t[k].x) <= 0 && dblcmp(t[i].y * t[k].y) <= 0) {
			break;
		}
		int a2 = xx(t[k]);
		if ((a1 + 1) % 4 == a2) {
			++sum;
		}
		else if ((a1 + 2) % 4 == a2) {
			sum += (detSign > 0 ? 2 : -2);
		}
		else if ((a1 + 3) % 4 == a2) {
			--sum;
		}
		a1 = a2;
	}
	for (int j = 0; j < n; ++j) {
		t[j].x += p.x;
		t[j].y += p.y;
	}
	return (i < n) ? 2 : (sum ? 1 : 0);
}
int main() {
	for (int i = 1; ~scanf("%d%d", &n, &m) && n; ++i) {
		i != 1 ? putchar(10) : 0;
		printf("Problem %d", i);
		putchar(58);
		putchar(10);
		for (int j = 0; j < n; ++j) {
			scanf("%lf%lf", &pts[j].x, &pts[j].y);
		}
		for (int j = 0; j < m; ++j) {
			scanf("%lf%lf", &p.x, &p.y);
			if (chk(pts, p)) {
				puts("Within");
			}
			else {
				puts("Outside");
			}
		}
	}
}