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
void write(int x) {
	int len_s = 0, str[10];
	while (x > 9) {
		str[len_s++] = x % 10 ^ 48;
		x /= 10;
	}
	str[len_s] = x % 10 ^ 48;
	for (int i = len_s; i >= 0; --i) {
		putchar(str[i]);
	}
}
int min(int a, int b) {
	return a < b ? a : b;
}
int max(int a, int b) {
	return a > b ? a : b;
}
int fstpow(int a, int b) {
	a %= MOD;
	int res = 1;
	while (b) {
		if (b & 1) {
			res = 1ll * res * a % MOD;
		}
		a = a * a % MOD;
		b >>= 1;
	}
	return res;
}
int n, k, a[200001], burn[200001], ans;
int main() {
	#ifndef __WIN32
	FileIO("fire");
	#endif
	read(&n);
	read(&k);
	for (int i = 1; i <= n; ++i) {
		read(&a[i]);
		burn[i] = burn[i - 1];
		if (a[i] == 100) {
			++burn[i];
			a[i] = a[i - 1]; 
		}
		a[i] = 570000004ll * (100 - a[i]) % MOD * a[i - 1] % MOD;
	}
	for (int i = 1; i <= n; ++i) {
		(ans+=1ll-1ll*a[min(i+k,n)]*fstpow(a[max(i-k-1,0)],MOD-2)%MOD*fstpow(0,burn[min(i+k,n)]-burn[max(i-k-1,0)])%MOD+MOD)%=MOD;
	}
    printf("%d\n",ans);
}
