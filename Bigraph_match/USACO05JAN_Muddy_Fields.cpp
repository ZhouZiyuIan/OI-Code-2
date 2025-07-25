//
// Created by 118 on 25-7-25.
//
#pragma GCC optimize(3, "Ofast", "inline")
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
		if (s == 45)f = -f;
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
		putchar_unlocked(45);
	}
	if (x > 9) write(x / 10);
	putchar_unlocked(x % 10 + 48);
}
int r, c, cnt1 = 1, cnt2 = 1, h[1001][1001], w[1001][1001], cnt, nxt[1000001], to[1000001], head[1000001], vis[1000001], link[1000001];
void add(int x, int y) {
	nxt[++cnt] = head[x];
	to[cnt] = y;
	head[x] = cnt;
}
char s[1001][1001];
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
	for (int i = 1; i < cnt1; ++i) {
		for (int j = 1; j <= 1000000; ++j) {
			vis[j] = 0;
		}
		if (find(i)) {
			++ans;
		}
	}
	return ans;
}
int main() {
	read(&r);
	read(&c);
	for (int i = 1; i <= r; ++i) {
		scanf("%s", s[i] + 1);
		for (int j = 1; j <= c; ++j) {
			if (s[i][j] == 42) {
				h[i][j] = s[i - 1][j] == 42 ? h[i - 1][j] : cnt1++;
				w[i][j] = s[i][j - 1] == 42 ? w[i][j - 1] : cnt2++;
				add(h[i][j], w[i][j]);
			}
		}
	}
	printf("%d", Hungary());
}
