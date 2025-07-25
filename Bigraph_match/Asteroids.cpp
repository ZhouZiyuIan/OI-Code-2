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
		if (s == '-')f = -f;
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
		putchar_unlocked('-');
	}
	if (x > 9) write(x / 10);
	putchar_unlocked(x % 10 + '0');
}
int n, k, x, y, nxt[500001], to[500001], head[501], cnt, vis[501], link[501];
void add(int x, int y) {
	nxt[++cnt] = head[x];
	to[cnt] = y;
	head[x] = cnt;
}
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
	for (int i = 1; i <= n; ++i) {
		for (int j = 1;j <= n; ++j) {
			vis[j] = 0;
		}
		if (find(i)) {
			++ans;
		}
	}
	return ans;
}
int main() {
	read(&n);
	read(&k);
	for (int i = 0; i < k; ++i) {
		read(&x);
		read(&y);
		add(x,y);
	}
	write(Hungary());
}