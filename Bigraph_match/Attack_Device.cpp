/*
Created by 118 on 25-7-25.
*/
#pragma GCC optimize(3, "Ofast")
#include <stdio.h>
#include <ctype.h>
#ifdef _WIN64
#define getchar_unlocked() _getchar_nolock()
#define putchar_unlocked(_c) _putchar_nolock(_c)
#endif
void read(int *w) {
	int f = 1, x = 0;
	char s = getchar_unlocked();
	while (!isdigit(s)) {
		if (s == '-')f = -f;
		s = getchar_unlocked();
	}
	do {
		x = (x << 1) + (x << 3) + (s ^ 48);
		s = getchar_unlocked();
	} while (isdigit(s));
	x *= f;
	*w = x;
}
void write(int x) {
	if (x < 0) {
		x = -x;
		putchar_unlocked('-');
	}
	if (x > 9) write(x / 10);
	putchar_unlocked(x % 10 + '0');
}
int n, nxt[400001], to[400001], head[90001], cnt, vis[90001], link[90001], tot, fx[9] = {0, -1, -2, 1, 2, -1, -2, 1, 2}, fy[9] = {0, -2, -1, -2, -1, 2, 1, 2, 1};
char s[201][201], ch;
void add(int x, int y) {
	nxt[++cnt] = head[x];
	to[cnt] = y;
	head[x] = cnt;
}
int find(int x) {
	for (int i = head[x]; i; i = nxt[i]) {
		int y = to[i];
		if (vis[y]) {
			continue;
		}
		vis[y] = 1;
		if (!link[y] || find(link[y])) {
			link[y] = x;
			return 1;
		}
	}
	return 0;
}
int Hungary() {
	int ans = 0;
	for (int i = 1; i <= n * n; ++i) {
		for (int j = 1; j <= 90000; ++j) {
			vis[j] = 0;
		}
		if (find(i)) {
			++ans;
		}
	}
	return ans;
}
int main() {
	read(&n);
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			ch = getchar_unlocked();
			while (!isdigit(ch)) {
				ch = getchar_unlocked();
			}
			s[i][j] = ch;
		}
	}
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			if (s[i][j] == '1') {
				++tot;
				continue;
			}
			for (int k = 1; k <= 8; k++) {
				int x = i + fx[k], y = j + fy[k];
				if (s[x][y] == '1') {
					continue;
				}
				if (x >= 1 && x <= n && y >= 1 && y <= n && ((i + j) & 1) == 0) {
					add((i - 1) * n + j, (x - 1) * n + y + n * n);
				}
			}
		}
	}
	write(n * n - tot - Hungary());
}
