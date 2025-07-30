//
// Created by 118 on 25-7-29.
//
#include <stdio.h>
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
void read(int* w) {
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
int max(int a, int b) {
	return a > b ? a : b;
}
int abs(int x) {
	return x < 0 ? -x : x;
}
typedef struct {
	int l, r, s;
}node;
node a[51];
int n, i, j;
int main() {
	while (read(&n), n) {
		for (i = 1; i <= n; ++i) {
			read(&a[i].s);
			a[i].l = 0;
			for (j = 1; j < i; ++j) {
				a[i].l = max(a[i].l, a[j].r - abs(a[j].s - a[i].s));
			}
			a[i].r = a[i].l + (a[i].s << 1);
		}
		for (i = 1; i <= n; i++) {
			for (j = 1; j < i; j++) {
				if (a[i].l < a[j].r && a[j].s > a[i].s) {
					a[i].l = a[j].r;
				}
			}
			for (j = i + 1; j <= n; j++) {
				if (a[i].r > a[j].l && a[j].s > a[i].s) {
					a[i].r = a[j].l;
				}
			}
			if (a[i].l < a[i].r) {
				write(i);
				putchar(32);
			}
		}
		putchar(10);
	}
}
