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
int n, m, to[30001], nxt[30001], head[10001], cnt, dfn[10001], low[10001], time, ans, rt, p1, p2, num = 0;
void add(int a, int b) {
	to[cnt] = b;
	nxt[cnt] = head[a];
	head[a] = cnt++;
}
void tarjan(int u) {
	dfn[u] = low[u] = ++time;
	int num = 0;
	for (int i = head[u]; i != -1; i = nxt[i]) {
		int j = to[i];
		if (!dfn[j]) {
			tarjan(j);
			if (low[j] >= dfn[u]) {
				++num;
			}
			if (low[u] > low[j]) {
				low[u] = low[j];
			}
		} else if (low[u] > dfn[j]) {
			low[u] = dfn[j];
		}
	}
	if (u != rt) {
		++num;
	}
	if (ans < num) {
		ans = num;
	}
}
int main() {
	for (; ; ) {
		read(&n);
		read(&m);
		if (n == 0) {
			break;
		}
		num = ans = cnt = time = 0;
		memset(head, -1, sizeof(head));
		memset(dfn, 0, sizeof(dfn));
		while (m--) {
			read(&p1);
			read(&p2);
			add(p1, p2);
			add(p2, p1);
		}
		for (rt = 0; rt < n; rt++) {
			if (!dfn[rt]) {
				num++;
				tarjan(rt);
			}
		}
		write(ans + num - 1);
		putchar_unlocked(10);
	}
}