#include <stdio.h>
#include <stdlib.h>
typedef struct {
	int x1, y1, x2, y2;
} square;
square rect[5001];
int cmp1(const void *a, const void *b) {
	return ((square *)a)->x1 - ((square *)b)->x1 > 0 ? 1 : -1;
}
int cmp2(const void *a, const void *b) {
	return ((square *)a)->y1 - ((square *)b)->y1 > 0 ? 1 : -1;
}
int n, h[100001], ans;
void sol1() {
	for (int i = 0; i < 100001; ++i) {
		h[i] = -1;
	}
	qsort(rect + 1, n, sizeof(square), cmp1);
	for (int i = 1; i <= n; ++i) {
		for (int j = rect[i].y1; j < rect[i].y2; ++j) {
			if (h[j] < rect[i].x1) {
				ans += 2;
			}
			if (h[j] < rect[i].x2) {
				h[j] = rect[i].x2;
			}
		}
	}
}
void sol2() {
	for (int i = 0; i < 100001; ++i) {
		h[i] = -1;
	}
	qsort(rect + 1, n, sizeof(square), cmp2);
	for (int i = 1; i <= n; ++i) {
		for (int j = rect[i].x1; j < rect[i].x2; ++j) {
			if (h[j] < rect[i].y1) {
				ans += 2;
			}
			if (h[j] < rect[i].y2) {
				h[j] = rect[i].y2;
			}
		}
	}
}
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%d%d%d%d", &rect[i].x1, &rect[i].y1, &rect[i].x2, &rect[i].y2);
		rect[i].x1 += 10001;
		rect[i].y1 += 10001;
		rect[i].x2 += 10001;
		rect[i].y2 += 10001;
	}
	sol1();
	sol2();
	printf("%d", ans);
}