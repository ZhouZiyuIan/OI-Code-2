#include <stdio.h>
int n, w, x, b, maxx, ans = -1;
long long sum[200001];
int main() {
	scanf("%d%d", &n, &w);
	for (int i = 0; i < n; ++i) {
		scanf("%d%d", &x, &b);
		sum[x] += b;
		maxx < x ? maxx = x : 0;
	}
	for (int i = 1; i <= maxx; ++i) {
		sum[i] += sum[i - 1];
	}
	for (int i = 1; i < maxx - w; ++i) {
		ans < (sum[i - 1 + w] - sum[i - 1]) ? ans = (sum[i - 1 + w] - sum[i - 1]) : 0;
	}
	printf("%d", ans);
}
