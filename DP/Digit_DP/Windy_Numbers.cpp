#include<stdio.h> 
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
typedef long long ll;
void read(ll *w) {
	ll f = 1, x = 0;
	char s = getchar_unlocked();
	while (!isdigit(s)) {
		if (s == 45) {
			f = -f;
		}
		s = getchar_unlocked();
	}
	do {
		x = (x << 1ll) + (x << 3ll) + (s ^ 48);
		s = getchar_unlocked();
	} while (isdigit(s));
	x *= f;
	*w = x;
}
void write(ll x) {
	if (x < 0) {
		x = -x;
		putchar_unlocked(45);
	}
	if (x > 9) {
		write(x / 10);
	}
	putchar_unlocked(x % 10 + 48);
}
ll a, b, f[20][12];
int dim[20];
int abs(int x) {
	return x < 0 ? -x : x;
}
ll dfs(int x, int pre, int mark) {
	if (x == 0) {
		return 1;
	}
	if (mark == 0 && f[x][pre] != -1) {
		return f[x][pre];
	}
	int maxn = mark ? dim[x] : 9;
	ll tmp = 0;
	for (int i = 0; i <= maxn; ++i) {
		if (abs(pre - i) < 2) {
			continue;
		}
		if (pre == 11 && i == 0) {
			tmp += dfs(x - 1, 11, mark && i == maxn);
		}
		else {
			tmp += dfs(x - 1, i, mark && i == maxn);
		}
	}
	if (mark == 0) {
		f[x][pre] = tmp;
	}
	return tmp;
}
ll ask(ll x) {
	dim[0] = 0;
	while (x) {
		dim[++dim[0]] = x % 10;
		x /= 10;
	}
	dim[dim[0] + 1] = -1;
	return dfs(dim[0], 11, 1);
}
int main() {
	read(&a);
	read(&b);
	for (int i = 0; i < 20; ++i) {
		for (int j = 0; j < 12; ++j) {
			f[i][j] = -1;
		}
	}
	write(ask(b) - ask(a - 1));
}