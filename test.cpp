#include <stdio.h>
typedef long long ll;
int n, q, m, a[100001], op, x, y, k;
ll mlt[400001], lzt[400001], seg[400001];
void pushup(const int x) {
	seg[x] = (seg[x << 1] + seg[x << 1 | 1]) % m;
}
void pushdown(const int i, const int s, const int t) {
	const int l = (i << 1), r = (i << 1) | 1, mid = (s + t) >> 1;
	if (mlt[i] != 1) {
		mlt[l] = (mlt[l] * mlt[i]) % m;
		mlt[r] = (mlt[r] * mlt[i]) % m;
		lzt[l] = (lzt[l] * mlt[i]) % m;
		lzt[r] = (lzt[r] * mlt[i]) % m;
		seg[l] = (seg[l] * mlt[i]) % m;
		seg[r] = (seg[r] * mlt[i]) % m;
		mlt[i] = 1;
	}
	if (lzt[i]) {
		seg[l] = (seg[l] + lzt[i] * (mid - s + 1)) % m;
		seg[r] = (seg[r] + lzt[i] * (t - mid)) % m;
		lzt[l] = (lzt[l] + lzt[i]) % m;
		lzt[r] = (lzt[r] + lzt[i]) % m;
		lzt[i] = 0;
	}
}
void build(const int x, const int l, const int r) {
	mlt[x] = 1;
	lzt[x] = 0;
	if (l == r) {
		seg[x] = a[l] % m;
		return;
	}
	int mid = (l + r) >> 1;
	build(x << 1, l, mid);
	build(x << 1 | 1, mid + 1, r);
	pushup(x);
}
void mul(const int x, const int l, const int r, const int gl, const int gr, const int val) {
	if (gl <= l && r <= gr) {
		mlt[x] = (mlt[x] * val) % m;
		seg[x] = (seg[x] * val) % m;
		lzt[x] = (lzt[x] * val) % m;
		return;
	}
	pushdown(x, l, r);
	const int mid = (l + ((r - l) >> 1));
	if (mid >= gl) {
		mul(x << 1, l, mid, gl, gr, val);
	}
	if (mid + 1 <= gr) {
		mul(x << 1 | 1, mid + 1, r, gl, gr, val);
	}
	pushup(x);
}
void add(const int x, const int l, const int r, const int gl, const int gr, const int val) {
	if (gl <= l && r <= gr) {
		seg[x] = (seg[x] + (ll) val * (r - l + 1)) % m;
		lzt[x] = (lzt[x] + val) % m;
		return;
	}
	pushdown(x, l, r);
	const int mid = (l + ((r - l) >> 1));
	if (mid >= gl) {
		add(x << 1, l, mid, gl, gr, val);
	}
	if (mid + 1 <= gr) {
		add(x << 1 | 1, mid + 1, r, gl, gr, val);
	}
	pushup(x);
}
ll que(const int x, const int l, const int r, const int gl, const int gr) {
	if (gl <= l && r <= gr) {
		return seg[x] % m;
	}
	pushdown(x, l, r);
	ll tot = 0;
	const int mid = (l + ((r - l) >> 1));
	if (mid >= gl) {
		tot += que(x << 1, l, mid, gl, gr);
	}
	if (mid + 1 <= gr) {
		tot += que(x << 1 | 1, mid + 1, r, gl, gr);
	}
	return tot % m;
}
int main() {
	scanf("%d%d%d", &n, &q, &m);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &a[i]);
	}
	build(1, 1, n);
	while (q--) {
		scanf("%d%d%d", &op, &x, &y);
		if (op == 1) {
			scanf("%d", &k);
			mul(1, 1, n, x, y, k);
		}
		else if (op == 2) {
			scanf("%d", &k);
			add(1, 1, n, x, y, k);
		}
		else {
			printf("%lld\n", que(1, 1, n, x, y));
		}
	}
}