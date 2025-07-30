#include <stdio.h>
int n, m, x1, y1, x2, y2, u[5001], l[5001], ans[5001], x, y, j;
double Det(double x1, double y1, double x2, double y2) {
	return x1 * y2 - x2 * y1;
}
int main() {
	while (~scanf("%d%d%d%d%d%d", &n, &m, &x1, &y1, &x2, &y2) && n) {
		for (int i = 0; i < n; ++i) {
			scanf("%d%d", &u[i], &l[i]);
			ans[i] = 0;
		}
		ans[n] = 0;
		for (int i = 0; i < m; ++i) {
			scanf("%d%d", &x, &y);
			for (j = 0; j < n; ++j) {
				if (Det(u[j] - x, y1 - y, l[j] - x, y2 - y) <= 0) {
					break;
				}
			}
			++ans[j];
		}
		for (int i = 0; i <= n; ++i) {
			printf("%d: %d\n", i, ans[i]);
		}
		putchar(10);
	}
}