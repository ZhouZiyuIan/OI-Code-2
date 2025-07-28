//
// Created by 118 on 25-7-27.
//
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
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
int max(int a, int b) {
	return a > b ? a : b;
}
int n, m, tot, sum, ans, a[1001][1001], b[1001][1001], p[1001], g[1001], mp[1000001], mp2[1000001], ap[1000001], fa[1001];
bool flag, flag1, fl[1001], fla[1001];
int find(int x) {
	if (x == fa[x]) {
		return x;
	}
	else {
		fa[x] = find(fa[x]);
		return fa[x];
	}
}
void add(int x, int y) {
	int fx = find(fa[x]), fy = find(fa[y]);
	if (fx != fy) {
		fa[fx] = fy;
		fl[fy] |= fl[fx];
	}
}
int lower_bound(int a[], int left, int right, int key) {
	while (left < right) {
		int mid = left + right >> 1;
		if (a[mid] > key) {
			right = mid;
		}
		else if (a[mid] == key) {
			return mid;
		}
		else {
			left = mid + 1;
		}
	}
	return left;
}
int lis(int x) {
	int len = 0, maxx = 0;
	for (int i = 1; i <= x; ++i) {
		int k = lower_bound(g, 1, 1 + len, p[i]);
		maxx = max(maxx, k);
		g[k] = p[i];
		len = max(len, k);
	}
	return maxx;
}
int main() {
	read(&n);
	read(&m);
	for (int i = 1; i <= n; ++i) {
		fa[i] = i;
		fl[i] = 0;
		for (int j = 1; j <= m; ++j) {
			read(&a[i][j]);
			mp[a[i][j]] = i;
			if (a[i][j]) {
				++tot;
			}
			else {
				fl[i] = flag = 1;
			}
		}
	}
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			read(&b[i][j]);
			mp2[b[i][j]] = i;
			if (a[i][j] != b[i][j]) {
				add(i, mp[b[i][j]]);
				flag1 = 1;
			}
		}
	}
	if (!flag) {
		if (flag1) {
			putchar_unlocked(45);
			putchar_unlocked(49);
		}
		else {
			putchar_unlocked(48);
		}
		return 0;
	}
	ans = tot;
	for (int i = 1; i <= n; ++i) {
		int cnt = 0, num = 0;
		for (int j = 1; j <= m; ++j) {
			if (b[i][j] && mp[b[i][j]] == mp2[b[i][j]]) {
				ap[b[i][j]] = ++cnt;
			}
		}
		for (int j = 1; j <= m; ++j) {
			if (a[i][j] && mp[a[i][j]] == mp2[a[i][j]]) {
				p[++num] = ap[a[i][j]];
			}
		}
		ans -= lis(num);
	}
	for (int i = 1; i <= n; ++i) {
		int fx = find(fa[i]);
		if (!fla[fx]) {
			fla[fx] = 1;
			flag = 0;
			for (int j = 1; j <= m; ++j) {
				if (a[i][j] != b[i][j]) {
					flag = 1;
					break;
				}
			}
			if (!fl[fx] && flag) {
				++ans;
			}
		}
	}
	write(ans);
}