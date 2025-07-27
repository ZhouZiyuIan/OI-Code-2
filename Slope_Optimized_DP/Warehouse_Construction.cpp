#include <stdio.h>
int n, head = 1, tail = 1, i, j;
long long x[1000001], p[1000001], c[1000001], s[1000001], g[1000001], f[1000001], ans, q[1000001];
double slope(int i, int j) {
	double a = ((s[j] - s[i]) * 1.0), b = f[j] - f[i] + g[j] - g[i];
	return b / a;
}
int main() {
	scanf("%d", &n);
	for (i = 1; i <= n; ++i) {
		scanf("%lld%lld%lld", &x[i], &p[i], &c[i]);
		s[i] = s[i - 1] + p[i];
		g[i] = g[i - 1] + p[i] * x[i];
	}
	for (i = 1; i <= n; ++i) {
		while (head < tail && slope(q[head], q[head + 1]) <= x[i]) {
			++head;
		}
		f[i] = f[q[head]] + x[i] * (s[i - 1] - s[q[head]]) - g[i - 1] + g[q[head]] + c[i];
		while (head < tail && slope(q[tail - 1], i) <= slope(q[tail - 1], q[tail])) {
			--tail;
		}
		q[++tail] = i;
	}
	head = n;
	ans = f[n];
	while (head && s[head] == s[head - 1]) {
		--head;
		ans > f[head] ? ans = f[head] : 0;
	}
	printf("%lld", ans);
}