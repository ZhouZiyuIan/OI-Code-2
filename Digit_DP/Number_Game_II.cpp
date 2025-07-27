//
// Created by 118 on 25-7-26.
//
#include <stdio.h>
#include <stdbool.h>
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
int a, b, N, f[11][100], digit[11];
int dfs(int pos, int sum, bool limit) {
	if (pos == 0) {
		return sum % N == 0;
	}
	if (~f[pos][sum] && !limit) {
		return f[pos][sum];
	}
	int up = limit ? digit[pos] : 9 , ans = 0;
	for (int k = 0; k <= up; ++k) {
		ans += dfs(pos - 1, sum + k, limit && k == up);
	}
	if (!limit) {
		f[pos][sum] = ans;
	}
	return ans;
}
int ask(int x) {
	for (int i = 0; i < 11; ++i) {
		for (int j = 0; j < 100; ++j) {
			f[i][j] = -1;
		}
	}
	int len = 0;
	while (x) {
		digit[++len] = x % 10;
		x /= 10;
	}
	return dfs(len, 0, 1);
}
int main() {
	while (~(read(&a), read(&b), read(&N))) {
		write(ask(b) - ask(a - 1));
		putchar_unlocked(10);
	}
}