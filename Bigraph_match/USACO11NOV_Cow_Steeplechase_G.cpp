//
// Created by 118 on 25-7-25.
//
#include <stdio.h>
#ifdef _WIN64
#define getchar_unlocked() _getchar_nolock()
#define putchar_unlocked(_c) _putchar_nolock(_c)
#endif
#define _U 0x01
#define _L 0x02
#define _D 0x04
#define _C 0x08
#define _P 0x10
#define _S 0x20
#define _X 0x40
#define _SP 0x80
extern unsigned char _ctype[];
#define isdigit(c) ((_ctype+1)[c]&(_D))
unsigned char _ctype[]={0x00,_C,_C,_C,_C,_C,_C,_C,_C,_C,_C|_S,_C|_S,_C|_S,_C|_S,_C|_S,_C,_C,_C,_C,_C,_C,_C,_C,_C,_C,_C,_C,_C,_C,_C,_C,_C,_C,_S|_SP,_P,_P,_P,_P,_P,_P,_P,_P,_P,_P,_P,_P,_P,_P,_P,_D,_D,_D,_D,_D,_D,_D,_D,_D,_D,_P,_P,_P,_P,_P,_P,_P,_U|_X,_U|_X,_U|_X,_U|_X,_U|_X,_U|_X,_U,_U,_U,_U,_U,_U,_U,_U,_U,_U,_U,_U,_U,_U,_U,_U,_U,_U,_U,_U,_P,_P,_P,_P,_P,_P,_L|_X,_L|_X,_L|_X,_L|_X,_L|_X,_L|_X,_L,_L,_L,_L,_L,_L,_L,_L,_L,_L,_L,_L,_L,_L,_L,_L,_L,_L,_L,_L,_P,_P,_P,_P,_C,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
void yyl(int *w) {
	int f = 1, x = 0;
	char s = getchar_unlocked();
	while (!isdigit(s)) {
		if (s == 45) {
			f = -f;
		}
		s = getchar_unlocked();
	}
	do {
		x = (x << 1) + (x << 3) + (s ^ 48);
		s = getchar_unlocked();
	} while (isdigit(s));
	x *= f;
	*w = x;
}
void czy(int x) {
	if (x < 0) {
		x = -x;
		putchar_unlocked(45);
	}
	if (x > 9) {
		czy(x / 10);
	}
	putchar_unlocked(x % 10 + 48);
}
int n, x1[251], y1[251], x2[251], y2[251], a[251], mpz, cnt, head[501], to[70001], nxt[70001], link[501], vis[501], tmp;
void add(int x, int y) {
	nxt[++cnt] = head[x];
	to[cnt] = y;
	head[x] = cnt;
}
int ljy(int u) {
	vis[u] = 1;
	for (int i = head[u]; i; i = nxt[i]) {
		int v = to[i];
		if (vis[link[v]]) {
			continue;
		}
		if (!link[v] || ljy(link[v])) {
			link[v] = u;
			return 1;
		}
	}
	return 0;
}
int cjr() {
	int ans = 0;
	for (int i = 1; i <= n; ++i) {
		if (a[i] == 2) {
			continue;
		}
		for (int j = 0; j <= n; ++j) {
			vis[j] = 0;
		}
		if (ljy(i)) {
			++ans;
		}
	}
	return ans;
}
int main() {
	yyl(&n);
	for (int i = 1; i <= n; ++i) {
		yyl(&x1[i]);
		yyl(&y1[i]);
		yyl(&x2[i]);
		yyl(&y2[i]);
		if (x1[i] > x2[i]) {
			tmp = x1[i];
			x1[i] = x2[i];
			x2[i] = tmp;
		}
		if (y1[i] > y2[i]) {
			tmp = y1[i];
			y1[i] = y2[i];
			y2[i] = tmp;
		}
		if (x1[i] == x2[i]) {
			a[i] = 1;
			++mpz;
		}
		else {
			a[i] = 2;
		}
	}
	for (int i = 1; i < n; ++i) {
		for (int j = i + 1; j <= n; ++j) {
			if (a[i] == 1 && a[j] == 2) {
				if (x1[i] >= x1[j] && x2[i] <= x2[j] && y1[j] >= y1[i] && y2[j] <= y2[i]) {
					add(i, j + mpz);
				}
			}
			if (a[i] == 2 && a[j] == 1) {
				if (x1[j] >= x1[i] && x2[j] <= x2[i] && y1[i] >= y1[j] && y2[i] <= y2[j]) {
					add(j, i + mpz);
				}
			}
		}
	}
	czy(n - cjr());
}