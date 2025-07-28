//
// Created by 118 on 25-7-28.
//
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
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
typedef struct{
	int nxt,to,dis;
}edg;
edg e[400001];
int n, m, cnt, head[100001], u, v, d[100001], val[200001], dis[200001], q, ans, p[31];
char c[100001];
void add(int from, int to, int dis) {
	e[++cnt].nxt = head[from];
	e[cnt].to = to;
	e[cnt].dis = dis;
	head[from] = cnt;
}
void dfs(int x, int y) {
	c[x] = 1;
	for (int i = head[x]; i; i = e[i].nxt) {
		if (!c[e[i].to]) {
			dfs(e[i].to, x);
			d[x] ^= d[e[i].to];
			val[e[i].dis] = d[e[i].to];
		}
		else if (e[i].to ^ y && !val[e[i].dis]) {
			val[e[i].dis] = rand();
			d[x] ^= val[e[i].dis];
			d[e[i].to] ^= val[e[i].dis];
		}
	}
}
int ins(int x){
	for (int i = 30; ~i; --i) {
		if (x & (1 << i)) {
			if (!p[i]) {
				p[i] = x;
				return 1;
			}
			x ^= p[i];
		}
	}
	return 0;
}
int main() {
	srand(time(0));
	read(&n);
	read(&m);
	for (int i = 1; i <= m; ++i) {
		read(&u);
		read(&v);
		add(u, v, i);
		add(v, u, i);
	}
	dfs(1, 1);
	read(&q);
	while (q--) {
		read(&u);
		ans = 1;
		for (int i = 0; i <= 30; ++i) {
			p[i] = 0;
		}
		while (u--) {
			read(&v);
			ans &= ins(val[v]);
		}
		puts(ans ? "Connected" : "Disconnected");
	}
}