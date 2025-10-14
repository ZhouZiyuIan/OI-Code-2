//
// Created by 118 on 25-10-14.
//
#include <stdio.h>
#define FileIO(str) freopen(str".in", "r", stdin); freopen(str".out", "w", stdout)
#define _U 0x01
#define _L 0x02
#define _D 0x04
#define _C 0x08
#define _P 0x10
#define _S 0x20
#define _X 0x40
#define _SP 0x80
#define MOD 1000000007
#define B 62
extern unsigned char _ctype[];
#define isdigit(c) ((_ctype + 1)[c] & (_D))
unsigned char _ctype[] = {
	0x00, _C, _C, _C, _C, _C, _C, _C, _C, _C, _C | _S, _C | _S, _C | _S, _C | _S, _C | _S, _C, _C, _C, _C, _C, _C, _C, _C, _C, _C, _C, _C, _C, _C, 
	_C, _C, _C, _C, _S | _SP, _P, _P, _P, _P, _P, _P, _P, _P, _P, _P, _P, _P, _P, _P, _P, _D, _D, _D, _D, _D, _D, _D, _D, _D, _D, _P, _P, _P, _P, _P, _P, 
	_P, _U | _X, _U | _X, _U | _X, _U | _X, _U | _X, _U | _X, _U, _U, _U, _U, _U, _U, _U, _U, _U, _U, _U, _U, _U, _U, _U, _U, _U, _U, _U, _U, _P, 
	_P, _P, _P, _P, _P, _L | _X, _L | _X, _L | _X, _L | _X, _L | _X, _L | _X, _L, _L, _L, _L, _L, _L, _L, _L, _L, _L, _L, _L, _L, _L, _L, _L, _L, 
	_L, _L, _L, _P, _P, _P, _P, _C, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};
void read(int *w) {
	int f = 1, x = 0, s = getchar();
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
void readL(long long *w) {
	int f = 1, s = getchar();
	long long x = 0;
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
void write(long long x) {
	if (x < 0) {
		putchar(45);
		x = -x;
	}
	if (x > 9) {
		write(x / 10);
	}
	putchar((int) (x % 10ll) ^ 48);
}
int f[63][63][63], T, s, z;
long long f1[63][63][63], n, dis, nw;
int max(const int i, const int i1) {
	return i > i1 ? i : i1;
}
int main() {
#ifndef __WIN32
	FileIO("c");
#endif
	read(&T);
	for (int j = 0; j <= B; ++j) {
		f[0][j][0] = max(0, j - 1);
		f1[0][j][0] = 1;
		for (int k = 1; k <= B; ++k) {
			f[0][j][k] = k - 1;
			f1[0][j][k] = 0;
		}
	}
	for (int i = 1; i <= B; ++i) {
		for (int j = 0; j <= B - i; ++j) {
			for (int k = 0; k <= B; ++k) {
				f[i][j][k] = f[i - 1][j + 1][f[i - 1][j][k]];
				f1[i][j][k] = f1[i - 1][j + 1][f[i - 1][j][k]] + f1[i - 1][j][k];
			}
		}
	}
	readL(&n);
	s = z = dis = nw = 0;
	for (int i = B; i >= 0; --i) {
		if (nw + (1ll << i) + f[i][s][z] <= n) {
			nw += 1ll << i;
			dis += f1[i][s][z];
			z = f[i][s][z];
			++s;
		}
	}
	write((nw == n ? dis : 0) - 1);
	putchar(10);
}