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

long long fstpow(long long a, long long b) {
	a %= MOD;
	long long res = 1;
	while (b) {
		if (b & 1) {
			res = res * a % MOD;
		}
		a = a * a % MOD;
		b >>= 1;
	}
	return res;
}

long long min(const long long a, const long long b) {
	return a < b ? a : b;
}

long long max(const long long a, const long long b) {
	return a > b ? a : b;
}
int T;
long long n, a, b;
int main() {
#ifndef __WIN32
	FileIO("sosoo");
#endif
	read(&T);
	while (T--) {
		readL(&n);
		readL(&a);
		readL(&b);
		for (long long i = 1ll; i <= min(n, 5ll); ++i) {
			const long long A = a, B = b;
			a = max((B << 1ll) - i, A + i);
			b = max((A << 1ll) - i, B + i);
		}
		a %= MOD;
		b %= MOD;
		n -= 5ll;
		if (n <= 0ll) {
			write(a);
			putchar(32);
			write(b);
			putchar(10);
			continue;
		}
		const long long t = fstpow(2, n), x = (2 * MOD - 6 * (t + MOD - 1) % MOD - t + n + 1) % MOD;
		if (n & 1) {
			write((b * t % MOD + x) % MOD);
			putchar(32);
			write((a * t % MOD + x) % MOD);
			putchar(10);
		}
		else {
			write((a * t % MOD + x) % MOD);
			putchar(32);
			write((b * t % MOD + x) % MOD);
			putchar(10);
		}
	}
}