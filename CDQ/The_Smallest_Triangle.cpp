//
// Created by 118 on 25-7-28.
//
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#ifdef _WIN64
#define getchar_unlocked() _getchar_nolock()
#endif
void read(int* w) {
	int f = 1, x = 0;
	char s = getchar_unlocked();
	while (!isdigit(s)) {
		if (s == 45) f = -f;
		s = getchar_unlocked();
	}
	do {
		x = (x << 1) + (x << 3) + (s ^ 48);
		s = getchar_unlocked();
	} while (isdigit(s));
	*w = x * f;
}
int min(int a, int b) {
	return a < b ? a : b;
}
double dmin(double a, double b) {
	return a < b ? a : b;
}
int n;
typedef struct{
	double x, y;
}point;
point p[200001];
double ans = 1e16;
int cmp(const void *a, const void *b) {
	return (((point*)a) -> x) - (((point*)b) -> x);
}
inline double dis(double x1, double y1, double x2, double y2) {
	return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}
void rotate(double t){
	t = t / 180 * 3.14159265358979323846;
	for (int i = 1; i <= n; ++i) {
		double x = p[i].x, y = p[i].y;
		p[i].x = x * cos(t) - y * sin(t);
		p[i].y = x * sin(t) + y * cos(t);
	}
	qsort(p + 1, n, sizeof(point), cmp);
	for (int i = 1; i < n - 1; ++i) {
		for (int j = i + 1; j < min(i + 20, n); ++j){
			for (int k = j + 1; k <= min(i + 20, n); ++k) {
				ans = dmin(ans, dis(p[i].x, p[i].y, p[j].x, p[j].y) + dis(p[j].x, p[j].y, p[k].x, p[k].y) + dis(p[i].x, p[i].y, p[k].x, p[k].y));
			}
		}
	}
}
int main() {
	srand(time(0));
	read(&n);
	for (int i = 1; i <= n; ++i) {
		scanf("%lf%lf", &p[i].x, &p[i].y);
	}
	rotate(rand() % 360);
	rotate(rand() % 360);
	printf("%lf", ans);
}