/*
Created by 118 on 25-7-25.
*/
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
int n, k, x, y, nxt[5001], to[5001], head[5001], cnt, vis[5001], link[5001], f[5001];
void add(int x, int y) {
	nxt[++cnt] = head[x];
	to[cnt] = y;
	head[x] = cnt;
}
int find(int x, int tag) {
	if (vis[x] == tag) {
		return 0;
	}
	vis[x] = tag;
	for (int i = head[x]; i; i = nxt[i]) {
		int y = to[i];
		if (!link[y] || find(link[y], tag)) {
			link[y] = x;
			return 1;
		}
	}
	return 0;
}
void dfs(int x) {
	f[x] = 1;
	for (int i = head[x]; i; i = nxt[i]) {
		int y = to[i];
		if (~vis[y]) {
			vis[y] = -1;
			dfs(link[y]);
		}
	}
}
int main() {
	read(&n);
	read(&k);
	for (int i = 0; i < k; ++i) {
		read(&x);
		read(&y);
		add(x,y);
	}
	for (int i = 1; i <= n; ++i) {
		if (!find(i, i)) {
			dfs(i);
		}
	}
	for (int i = 1; i <= n; ++i) {
		if (f[i]) {
			putchar_unlocked(77);
			putchar_unlocked(105);
			putchar_unlocked(114);
			putchar_unlocked(107);
			putchar_unlocked(111);
		}
		else {
			putchar_unlocked(83);
			putchar_unlocked(108);
			putchar_unlocked(97);
			putchar_unlocked(118);
			putchar_unlocked(107);
			putchar_unlocked(111);
		}
		putchar_unlocked(10);
	}
}