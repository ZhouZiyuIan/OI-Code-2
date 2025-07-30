//
// Created by 118 on 25-7-30.
//
#include <stdio.h>
#include <stdlib.h>
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
unsigned char _ctype[] = {0x00,_C,_C,_C,_C,_C,_C,_C,_C,_C,_C | _S,_C | _S,_C | _S,_C | _S,_C | _S,_C,_C,_C,_C,_C,_C,_C,_C,_C,_C,_C,_C,_C,_C,_C,_C,_C,_C,_S | _SP,_P,_P,_P,_P,_P,_P,_P,_P,_P,_P,_P,_P,_P,_P,_P,_D,_D,_D,_D,_D,_D,_D,_D,_D,_D,_P,_P,_P,_P,_P,_P,_P,_U | _X,_U | _X,_U | _X,_U | _X,_U | _X,_U | _X,_U,_U,_U,_U,_U,_U,_U,_U,_U,_U,_U,_U,_U,_U,_U,_U,_U,_U,_U,_U,_P,_P,_P,_P,_P,_P,_L | _X,_L | _X,_L | _X,_L | _X,_L | _X,_L | _X,_L,_L,_L,_L,_L,_L,_L,_L,_L,_L,_L,_L,_L,_L,_L,_L,_L,_L,_L,_L,_P,_P,_P,_P,_C, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0 , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
void read(int *w) {
	int f = 1, x = 0;
	char s = getchar();
	while (!isdigit(s)) {
		if (s == 45) {
			f = -f;
		}
		s = getchar();
	}
	do {
		x = (x << 1) + (x << 3) + (s ^ 48);
		s = getchar();
	} while (isdigit(s));
	*w = x * f;
}
void write(int x) {
	if (x < 0) {
		x = -x;
		putchar(45);
	}
	if (x > 9) {
		write(x / 10);
	}
	putchar(x % 10 + 48);
}
typedef struct {
	int x, y;
}tree;
typedef struct {
	int x, y, id, w;
}node;
tree t[5000001];
node a[5000001];
int cmp(const void *a, const void *b) {
	return ((tree*)a) -> x > ((tree*)b) -> x ? 1 : -1;
}
int cmp1(const void *a, const void *b) {
	return ((node*)a) -> x > ((node*)b) -> x ? 1 : -1;
}
int n, m, cnt, xa, ya, xb, yb, tr[10000001], ans[5000001], cur = 1;
int lowbit(int x) {
	return x & -x;
}
void modify(int x, int k) {
	++x;
	while (x <= 10000000) {
		tr[x] += k;
		x += lowbit(x);
	}
}
int query(int x) {
	++x;
	int s = 0;
	while (x) {
		s += tr[x];
		x -= lowbit(x);
	}
	return s;
}
int main() {
	read(&n);
	read(&m);
	for (int i = 1; i <= n; ++i) {
		read(&t[i].x);
		read(&t[i].y);
	}
	for (int i = 1; i <= m; ++i){
		read(&xa);
		read(&ya);
		read(&xb);
		read(&yb);
		a[++cnt].id=cnt;
		a[cnt].w=1;
		a[cnt].x=xb;
		a[cnt].y=yb;
		a[++cnt].id = cnt;
		a[cnt].w = 1;
		a[cnt].x = xb;
		a[cnt].y = ya - 1;
		a[++cnt].id = cnt;
		a[cnt].w = 1;
		a[cnt].x = xa - 1;
		a[cnt].y = yb;
		a[++cnt].id = cnt;
		a[cnt].w = 1;
		a[cnt].x = xa - 1;
		a[cnt].y = ya - 1;
	}
	qsort(t + 1, n, sizeof(tree), cmp);
	qsort(a + 1, cnt, sizeof(node), cmp1);
	for (int i = 1; i <= cnt; ++i) {
		while (t[cur].x <= a[i].x && cur <= n) {
			modify(t[cur++].y, 1);
		}
		ans[a[i].id] += query(a[i].y);
	}
	for (int i = 1; i <= cnt; i += 4) {
		write(ans[i] - ans[i + 1] - ans[i + 2] + ans[i + 3]);
		putchar(10);
	}
}
