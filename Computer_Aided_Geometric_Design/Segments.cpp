#include <stdio.h>
#include <math.h>
const double eps = 1e-8;
double x[205], y[205];
int T, n, flag;
double times(int a, int b, int c) {
	return (x[a] - x[b]) * (y[a] - y[c]) - (x[a] - x[c]) * (y[a] - y[b]);
}
int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		int pcnt = n << 1;
		for (int i = 0; i < pcnt; i++) {
			scanf("%lf%lf", &x[i], &y[i]);
		}
		flag = 0;
		for (int i = 0; !flag && i < pcnt; i++) {
			for (int j = i + 1; !flag && j < pcnt; j++) {
				if (fabs(x[i] - x[j]) > eps || fabs(y[i] - y[j]) > eps) {
					int ok = 1;
					for (int k = 0; ok && k < n; k++) {
						int p1 = k * 2;
						int p2 = k * 2 + 1;
						double c1 = times(p1, i, j);
						double c2 = times(p2, j, i);
						if (c1 * c2 < -eps) {
							ok = 0;
						}
					}
					if (ok) {
						flag = 1;
					}
				}
			}
		}
		puts(flag ? "Yes!" : "No!");
	}
}