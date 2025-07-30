//
// Created by 118 on 25-7-28.
//
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#ifdef _WIN64
#define getchar_unlocked() _getchar_nolock()
#define putchar_unlocked(_c) _putchar_nolock(_c)
#endif
int read(int* w) {
	int f = 1, x = 0;
	char s = getchar_unlocked();
	while (!isdigit(s)) {
		if (s == 45){
			f = -f;
		}
		else if(s == -1){
			return -1;
		}
		else if(s == 10){
			return 10;
		}
		s = getchar_unlocked();
	}
	do {
		x = (x << 1) + (x << 3) + (s ^ 48);
		s = getchar_unlocked();
	} while (isdigit(s));
	*w = x * f;
	if(s == 10){
		return 10;
	}
	return 1;
}
void write(int x) {
	if (x < 0) {
		x = -x;
		putchar_unlocked(45);
	}
	if (x > 9) write(x / 10);
	putchar_unlocked(x % 10 + 48);
}
int n, x, y;
int dfn[101], low[101], tot;
int head[101], to[10001], nxt[10001], idx;
int b[101], ans;
void add(int u, int v) {
	to[idx] = v;
	nxt[idx] = head[u];
	head[u] = idx++;
}
void tarjan(int u, int rt) {
	dfn[u] = low[u] = ++tot;
	int son = 0;
	for (int i = head[u]; i != -1; i = nxt[i]) {
		int v = to[i];
		if (!dfn[v]) {
			++son;
			tarjan(v, rt);
			low[u] = (low[u] < low[v]) ? low[u] : low[v];
			if (low[v] >= dfn[u] && (rt != u || son > 1)) {
				b[u] = 1;
			}
		}
		else {
			low[u] = (low[u] < dfn[v]) ? low[u] : dfn[v];
		}
	}
}
int main() {
	for (; ; ) {
		read(&n);
		if (n == 0) {
			break;
		}
		memset(dfn, 0, sizeof(dfn));
		memset(low, 0, sizeof(low));
		memset(b, 0, sizeof(b));
		memset(head, -1, sizeof(head));
		idx = tot = ans = 0;
		for (; ; ) {
			read(&x);
			if (x == 0) {
				break;
			}
			for(; ; ) {
				int ret = read(&y);
				add(x, y);
				add(y, x);
				if (ret == 10) {
					break; 
				}
			}
		}
		for (int i = 1; i <= n; ++i) {
			if (!dfn[i]) {
				tarjan(i, i);
			}
		}
		for (int i = 1; i <= n; ++i) {
			if (b[i]) {
				++ans;
			}
		}
		write(ans);
		putchar_unlocked(10);
	}
}
