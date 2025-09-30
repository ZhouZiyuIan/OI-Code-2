//
// Created by 118 on 25-9-30.
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
unsigned char _ctype[] = {
	0x00,_C,_C,_C,_C,_C,_C,_C,_C,_C,_C | _S,_C | _S,_C | _S,_C | _S,_C | _S,_C,_C,_C,_C,_C,_C,_C,_C,_C,_C,_C,_C,_C,_C,
	_C,_C,_C,_C,_S | _SP,_P,_P,_P,_P,_P,_P,_P,_P,_P,_P,_P,_P,_P,_P,_P,_D,_D,_D,_D,_D,_D,_D,_D,_D,_D,_P,_P,_P,_P,_P,_P,
	_P,_U | _X,_U | _X,_U | _X,_U | _X,_U | _X,_U | _X,_U,_U,_U,_U,_U,_U,_U,_U,_U,_U,_U,_U,_U,_U,_U,_U,_U,_U,_U,_U,_P,
	_P,_P,_P,_P,_P,_L | _X,_L | _X,_L | _X,_L | _X,_L | _X,_L | _X,_L,_L,_L,_L,_L,_L,_L,_L,_L,_L,_L,_L,_L,_L,_L,_L,_L,
	_L,_L,_L,_P,_P,_P,_P,_C, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};
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
	}
	while (isdigit(s));
	x *= f;
	*w = x;
}
void write(int x) {
	if (x < 0) {
		putchar(45);
		x = -x;
	}
	if (x > 9) {
		write(x / 10);
	}
	putchar((x % 10) ^ 48);
}
#define MOD 998244353
int n, m, c[5001], d[5001], powC[5001], ans;
void add_mod(int *a, const int b) {
	*a += b;
	if (*a >= MOD) {
		*a -= MOD;
	}
}
int mul_mod(const long long a, const long long b) {
	return (int)((a * b) % MOD);
}
int main() {
#ifndef __WIN32
    freopen("piggy.in", "r", stdin);
    freopen("piggy.out", "w", stdout);
#endif
	read(&n);
	read(&m);
	for (int i = 1; i <= n; ++i) {
		read(&c[i]);
		read(&d[i]);
	}
	const long long C = (1LL * m * (m - 1) / 2) % MOD;
	powC[0] = 1;
	for (int i = 1; i <= n; ++i) {
		powC[i] = mul_mod(powC[i - 1], C);
	}
	for (int s = 1; (s << 1) <= n; ++s) {
		static int pb[5001], pB[5001];
		pb[0] = pB[0] = 0;
		for (int i = 1; i <= n - s; ++i) {
			int b = 0, B = 0;
			const int a1 = c[i], b1 = d[i], a2 = c[i + s], b2 = d[i + s];
			if (a1 == 0 && a2 == 0) {
				B = 1;
			}
			if (a1 != 0 && a2 != 0) {
				if (a1 != a2 || b1 != b2) {
					b = 1;
				}
			}
			pb[i] = pb[i - 1] + b;
			pB[i] = pB[i - 1] + B;
		}
		for (int u = 1; u <= n - (s << 1) + 1; ++u) {
			const int l = u, r = u + s - 1;
			if (pb[r] - pb[l - 1] == 0) {
				add_mod(&ans, powC[pB[r] - pB[l - 1]]);
			}
		}
	}
	write(ans);
}
