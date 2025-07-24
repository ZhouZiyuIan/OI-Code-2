//
// Created by 118 on 25-7-23.
//
#pragma GCC optimize(3,"Ofast")
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
		if(s == 45) {
			f = -f;
		}
		s = getchar_unlocked();
	}
	do {
		x = (x << 1) + (x << 3) + (s ^ 48);
		s = getchar_unlocked();
	} while(isdigit(s));
	x *= f;
	*w = x;
}
void write(int x) {
	if (x < 0) {
		x = -x;
		putchar_unlocked(45);
	}
	if (x > 9) {
		write(x / 10);
	}
	putchar_unlocked(x % 10 + 48);
}
int n, f[20001][3], u, v, w, ans, m, tmp, head[20001], cnt;
typedef struct {
	int to,val,nxt;
} edg;
edg e[40001];
void add(const int from, const int to, const int dis) {
	e[++cnt].nxt = head[from];
	e[cnt].to = to;
	e[cnt].val = dis;
	head[from] = cnt;
}
void dfs(int now, int fa) {
	f[now][0] = 1;
	for (int i = head[now]; i != 0; i = e[i].nxt) {
		int v = e[i].to;
		if (v == fa) {
			continue;
		}
		dfs(v, now);
		for (int j = 0; j < 3; ++j) {
			int mod = (3 - (((j + e[i].val) % 3 + 3) % 3)) % 3;
			ans += f[v][j] * f[now][mod] * 2;
		}
		for (int j = 0; j < 3; ++j) {
			int mod = ((j + e[i].val) % 3 + 3) % 3;
			f[now][mod] += f[v][j];
		}
	}
}
int gcd(int a, int b) {
	return b == 0 ? a : gcd(b, a % b);
}
int main() {
	read(&n);
	for (int i = 1; i < n; ++i) {
		int u, v, w;
		read(&u);
		read(&v);
		read(&w);
		add(u, v, w);
		add(v, u, w);
	}
	ans = n;
	dfs(1, -1);
	m = n * n;
	int tmp = gcd(ans, m);
	write(ans / tmp);
	putchar_unlocked(47);
	write(m / tmp);
	return 0;
}