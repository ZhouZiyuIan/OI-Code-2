#define scanf __builtin_scanf
#define printf __builtin_printf
int n, h[1000010], l[1000010], r[1000010], st[1000010][21], lg[1000010];
int gcd(int a, int b) {
	while (b) {
		const int tmp = a % b;
		a = b;
		b = tmp;
	}
	return a;
}
int query(const int L, const int R) {
	const int j = lg[R - L + 1];
	return gcd(st[L][j], st[R - (1 << j) + 1][j]);
}
int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; ++i) {
		scanf("%d", &h[i]);
	}
	lg[1] = 0;
	for (int i = 2; i <= n; ++i) {
		lg[i] = lg[i >> 1] + 1;
	}
	for (int i = 0; i < n; ++i) {
		st[i][0] = h[i];
	}
	for (int j = 1; (1 << j) <= n; ++j) {
		for (int i = 0; i + (1 << j) <= n; ++i) {
			st[i][j] = gcd(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
		}
	}
	for (int i = 0; i < n; ++i) {
		int l1 = 0, r1 = i, ret = i;
		while (l1 <= r1) {
			const int mid = (l1 + r1) >> 1;
			if (query(mid, i) == h[i]) {
				ret = mid;
				r1 = mid - 1;
			}
			else {
				l1 = mid + 1;
			}
		}
		l[i] = ret;
	}
	for (int i = 0; i < n; ++i) {
		int l1 = i, r1 = n - 1, ret = i;
		while (l1 <= r1) {
			const int mid = (l1 + r1) >> 1;
			if (query(i, mid) == h[i]) {
				ret = mid;
				l1 = mid + 1;
			}
			else {
				r1 = mid - 1;
			}
		}
		r[i] = ret;
	}
	for (int i = 0; i < n; ++i) {
		printf("%d ", r[i] - l[i] + 1);
	}
}