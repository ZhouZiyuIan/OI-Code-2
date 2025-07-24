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
		if (s == '-') f = -f;
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
		putchar_unlocked('-');
	}
	if (x > 9) write(x / 10);
	putchar_unlocked(x % 10 + '0');
}
int max(int a, int b) {
	return a > b ? a : b;
}
int min(int a, int b) {
	return a < b ? a : b;
}
int n, m, a, b, to[500001], nxt[500001], head[500001], dfn[500001], time, low[500001], top, cnt, stk[500001], vis[500001], mar[500001], du[500001], z, flag = 1, in[500001], i0;
void add(int x, int y){
	to[++z] = y;
	nxt[z] = head[x];
	head[x] = z;
}
void tarjan(int now) {
	dfn[now] = low[now] = ++time;
	stk[++top] = now;
	vis[now] = 1;
	for (int i = head[now]; i; i = nxt[i]) {
		int next = to[i];
		if (!dfn[next]) {
			tarjan(next);
			low[now] = min(low[now], low[next]);
		}
		else if (vis[next]) {
			low[now] = min(low[now], dfn[next]);
		}
	}
	if (low[now] == dfn[now]) {
		cnt = 0;
		int tmp;
		do {
			tmp = stk[top--];
			vis[tmp] = 0;
			mar[tmp] = now;
			++cnt;
		} while (tmp != now);
		if (cnt == n) {
			flag = 0;
		}
	}
}

int main() {
	read(&n);
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			read(&b);
			if (b) {
				add(i, j);
			}
		}
	}
	for (int i = 1; i <= n; ++i) {
		if (!dfn[i]) {
			tarjan(i);
		}
	}
	for (int i = 1; i <= n; ++i) {
		for (int j = head[i]; j; j = nxt[j]) {
			if (mar[i] != mar[to[j]]) {
				++in[mar[to[j]]];
			}
		}
	}
	for (int i = 1; i <= n; ++i) {
		if (mar[i] == i) {
			if (!in[i]) {
				++i0;
			}
		}
	}
	write(i0);
}