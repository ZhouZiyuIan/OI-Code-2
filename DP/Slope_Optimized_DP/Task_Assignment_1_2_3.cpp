//
// Created by 118 on 25-7-26.
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
unsigned char _ctype[]={0x00,_C,_C,_C,_C,_C,_C,_C,_C,_C,_C|_S,_C|_S,_C|_S,_C|_S,_C|_S,_C,_C,_C,_C,_C,_C,_C,_C,_C,_C,_C,_C,_C,_C,_C,_C,_C,_C,_S|_SP,_P,_P,_P,_P,_P,_P,_P,_P,_P,_P,_P,_P,_P,_P,_P,_D,_D,_D,_D,_D,_D,_D,_D,_D,_D,_P,_P,_P,_P,_P,_P,_P,_U|_X,_U|_X,_U|_X,_U|_X,_U|_X,_U|_X,_U,_U,_U,_U,_U,_U,_U,_U,_U,_U,_U,_U,_U,_U,_U,_U,_U,_U,_U,_U,_P,_P,_P,_P,_P,_P,_L|_X,_L|_X,_L|_X,_L|_X,_L|_X,_L|_X,_L,_L,_L,_L,_L,_L,_L,_L,_L,_L,_L,_L,_L,_L,_L,_L,_L,_L,_L,_L,_P,_P,_P,_P,_C,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int read(int *w) {
	int f = 1, x = 0;
	char s = getchar_unlocked();
	while (!isdigit(s)) {
		if (s == 45) {
			f = -f;
		}
		else if (s == -1) {
			return -1;
		}
		s = getchar_unlocked();
	}
	do {
		x = (x << 1ll) + (x << 3ll) + (s ^ 48);
		s = getchar_unlocked();
	} while (isdigit(s));
	x *= f;
	*w = x;
	return 1;
}
void write(long long x) {
	if (x < 0) {
		x = -x;
		putchar_unlocked(45);
	}
	if (x > 9) {
		write(x / 10);
	}
	putchar_unlocked(x % 10 + 48);
}
long long f[300001], sumt[300001], sumc[300001];
int q[300001], n, s, l = 1, r = 1, t, c;
int bs(int i, int k) {
	if (l == r) {
		return q[r];
	}
	int L = l, R = r, mid;
	while (L < R) {
		mid = (L + R) >> 1;
		if (f[q[mid + 1]] - f[q[mid]] <= k * (sumc[q[mid + 1]] - sumc[q[mid]])) {
			L = mid + 1;
		}
		else {
			R = mid;
		}
	}
	return q[L];
}
int main() {
	read(&n);
	read(&s);
	for (int i = 1; i <= n; ++i) {
		read(&t);
		read(&c);
		sumt[i] = sumt[i - 1] + t;
		sumc[i] = sumc[i - 1] + c;
	}
	for (int i = 1; i <= n; ++i) {
		int p = bs(i, s + sumt[i]);
		f[i] = f[p] - (s + sumt[i]) * sumc[p] + sumt[i] * sumc[i] + s * sumc[n];
		while (l < r && (f[q[r]] - f[q[r - 1]]) * (sumc[i] - sumc[q[r]]) >= (f[i] - f[q[r]]) * (sumc[q[r]] - sumc[q[r - 1]])) {
			--r;
		}
		q[++r] = i;
	}
	write(f[n]);
}