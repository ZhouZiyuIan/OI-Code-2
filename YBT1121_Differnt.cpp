#include <stdio.h>
#include <math.h>
int a[200001], f[2000001], q[200001], st[200001][20], n, m, l, r, t, p;
int max(int a, int b) {
	return a > b ? a : b;
}
int min(int a, int b) {
	return a < b ? a : b;
}
int lower_bound(int a[], int l, int r, const int key) {
	while (l <= r) {
		const int mid = (l + r) >> 1;
		if (a[mid] >= key) {
			r = mid - 1;
		}
		else {
			l = mid + 1;
		}
	}
	return l;
}
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &a[i]);
		a[i] += 1000000;
		q[i] = max(q[i - 1], f[a[i]] + 1);
		st[i][0] = i - q[i] + 1;
		f[a[i]] = i;
	}
	for (int i = 1; i < 20; ++i) {
		for (int j = 1; j + (1 << i) - 1 <= n; ++j) {
			st[j][i] = max(st[j][i - 1], st[j + (1 << i - 1)][i - 1]);
		}
	}
	while (m--) {
		scanf("%d%d", &l, &r);
		++l;
		++r;
		t = lower_bound(q, l - 1,r + 1, l);
		if (t > r) {
			printf("%d\n", r - l + 1);
		}
		else {
			p = log2(r - t + 1);
			printf("%d\n", max(t - l, max(st[t][p], st[r - (1 << p) + 1][p])));
		}
	}
}
