//
// Created by 118 on 25-7-28.
//
#include <stdio.h>
#include <ctype.h>
#include <string.h>
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
int n, m, x, y, cnt, tot, dfn[30001], low[30001], head[30001], to[60001], nxt[60001], idx;
void add(int a, int b) {
	to[idx] = b;
	nxt[idx] = head[a];
	head[a] = idx++;
}
void tarjan(int u, int fa) {
	dfn[u] = low[u] = ++tot;
	for (int i = head[u]; i != -1; i = nxt[i]) {
		int v = to[i];
		if (!dfn[v]) {
			tarjan(v, u);
			if (low[v] > dfn[u]) {
				++cnt;
			}
			if (low[u] > low[v]) {
				low[u] = low[v];
			}
		}
		else if (v != fa && low[u] > dfn[v]) {
			low[u] = dfn[v];
		}
	}
}
int main() {
	for (; ; ) {
		read(&n);
		read(&m);
		if (n == 0) {
			break;
		}
		cnt = tot = idx = 0;
		memset(head, -1, sizeof(head));
		memset(dfn, 0, sizeof(dfn));
		memset(low, 0, sizeof(low));
		while (m--) {
			read(&x);
			read(&y);
			add(x, y);
			add(y, x);
		}
		for (int i = 1; i <= n; ++i) {
			if (!dfn[i]) {
				tarjan(i, 0);
			}
		}
		write(cnt);
		putchar_unlocked(10);
	}
}