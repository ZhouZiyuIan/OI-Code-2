//
// Created by 118 on 25-7-28.
//
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#ifdef _WIN64
#define getchar_unlocked() _getchar_nolock()
#define putchar_unlocked(_c) _putchar_nolock(_c)
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
void write(int x) {
	if (x < 0) {
		x = -x;
		putchar_unlocked(45);
	}
	if (x > 9) write(x / 10);
	putchar_unlocked(x % 10 + 48);
}
int n, k, a[100001], b[100001], c[100001], la[200001], ra[200001], lb[200001], rb[200001], ab[100001], ba[100001], ac[100001], bc[100001], bel[200001], val[200001], sum[100001], ans[100001];
typedef struct {
	int a, b, c;
}query;
query q[100001];
int cmp(const void *a, const void *b) {
	query *x = (query *)a, *y = (query *)b;
	if (bel[x -> a] != bel[y -> a]) {
		return bel[x -> a] - bel[y -> a];
	}
	if (bel[x -> a] & 1) {
		return x -> b - y -> b;
	}
	return y -> b - x -> b;
}
inline void ins(int x) {
	++val[x];
	++sum[bel[x]];
}
inline void rmv(int x) {
	--val[x];
	--sum[bel[x]];
}
inline int que(int x) {
	int ret = 0;
	for (int i = 1; i < bel[x]; ++i) {
		ret += sum[i];
	}
	for (int i = x; bel[i] == bel[x]; --i) {
		ret += val[i];
	}
	return ret;
}
int main() {
	read(&n);
	read(&k);
	for (int i = 1; i <= n; ++i) {
		read(&a[i]);
		read(&b[i]);
		read(&c[i]);
		++ra[a[i]];
		++rb[b[i]];
	}
	for (int i = 1; i <= k; ++i) {
		la[i] = ra[i - 1] + 1;
		ra[i] += ra[i - 1];
		lb[i] = rb[i - 1] + 1;
		rb[i] += rb[i - 1];
	}
	for (int i = 1; i <= n; ++i) {
		int x = la[a[i]]++, y = lb[b[i]]++;
		q[i].a = ra[a[i]];
		q[i].b = rb[b[i]];
		q[i].c = c[i];
		ab[x] = y;
		ba[y] = x;
		ac[x] = bc[y] = c[i];
	}
	for (int i = 1; i <= n; ++i) {
		bel[i] = i / 1000;
	}
	qsort(q + 1, n, sizeof(query), cmp);
	for (int i = 1; i <= k; ++i) {
		bel[i] = (i - 1) / 300 + 1;
	}
	for (int i = 1, a = 0, b = 0; i <= n; ++i) {
		while (a < q[i].a) {
			if (ab[++a] <= b) {
				ins(ac[a]);
			}
		}
		while (a > q[i].a) {
			if (ab[a--] <= b) {
				rmv(ac[a + 1]);
			}
		}
		while (b < q[i].b) {
			if (ba[++b] <= a) {
				ins(bc[b]);
			}
		}
		while (b > q[i].b) {
			if (ba[b--] <= a) {
				rmv(bc[b + 1]);
			}
		}
		++ans[que(q[i].c) - 1];
	}
	for (int i = 0; i < n; ++i) {
		write(ans[i]);
		putchar_unlocked(10);
	}
}