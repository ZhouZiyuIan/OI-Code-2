#include <stdio.h>
#include <ctype.h>
#define getchar_unlocked getchar
#define putchar_unlocked putchar
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
int n, m, a, b, to[200001], nxt[200001], head[200001], dfn[200001], time, low[200001], top, cnt, stk[200001], vis[200001], mar[200001], du[200001], z, flag = 1, out[200001], in[200001], o0, i0;
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
	for (int i = 1; i <= n; i++) {
		while (read(&b), b) {
			add(i, b);
		}
	}
	for (int i = 1; i <= n; i++)if (!dfn[i])tarjan(i);
	for (int i = 1; i <= n; ++i) {
		for (int j = head[i]; j; j = nxt[j]) {
			if (mar[i] != mar[to[j]]) {
				++out[mar[i]];
				++in[mar[to[j]]];
			}
		}
	}
	for (int i = 1; i <= n; ++i) {
		if (mar[i] == i) {
			if (!in[i]) {
				++i0;
			}
			if (!out[i]) {
				++o0;
			}
		}
	}
	write(i0);
	putchar_unlocked('\n');
	write(flag ? max(i0, o0) : 0);
}
/*
 *天啊，什么千年前黑历史翻新
 *使用了本人 2024-12-07 的代码（大概？）改编而来
 */