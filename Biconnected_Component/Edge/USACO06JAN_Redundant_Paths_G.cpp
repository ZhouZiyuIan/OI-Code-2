//
// Created by 118 on 25-7-28.
//
#pragma GCC optimize(3, "Ofast", "inline")
#include <stdio.h>
#include <ctype.h>
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
int min(int a, int b) {
	return a < b ? a : b;
}
int f, r, head[5001], to[40002], nxt[40002], cnt = 1, dfn[5001], time, low[5001], top, stk[5001], v[40002], cl, c[5001], ct[5001], s;
void add(int u, int v) {
	nxt[++cnt] = head[u];
	to[cnt] = v;
	head[u] = cnt;
}
void tarjan(int now) {
	low[now] = dfn[now] = ++time;
	stk[++top] = now;
	for (int i = head[now]; i; i = nxt[i]) {
		if (!v[i ^ 1]) {
			v[i] = 1;
			if (!dfn[to[i]]) {
				tarjan(to[i]);
			}
			low[now] = min(low[now], low[to[i]]);
		}
	}
	if (low[now] == dfn[now]) {
		++cl;
		while (stk[top + 1] != now) {
			c[stk[top--]] = cl;
		}
	}
}
int main() {
	read(&f);
	read(&r);
	for (int i = 0, x, y; i < r; ++i) {
		read(&x);
		read(&y);
		add(x, y);
		add(y, x);
	}
	tarjan(1);
	for (int i = 2; i <= cnt; i += 2) {
		if (c[to[i]] != c[to[i ^ 1]]) {
			++ct[c[to[i]]];
			++ct[c[to[i ^ 1]]];
		}
	}
	for (int i = 1; i <= cl; ++i) {
		if (ct[i] == 1) {
			++s;
		}
	}
	write((s + 1) / 2);
	putchar_unlocked('\n');
	return 0;
}