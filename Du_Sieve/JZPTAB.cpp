#include <stdio.h>
#include <ctype.h>
#ifdef _WIN64
#define putchar_unlocked _putchar_nolock
#endif
char buf[1 << 10], *p1 = buf, *p2 = buf;
char nc() {
	if (p1 == p2) {
		p1 = buf;
		p2 = p1 + fread(buf, 1, sizeof(buf), stdin);
		if (p1 == p2) {
			return -1;
		}
		return *p1++;
	}
	return *p1++;
}
void read(int *w) {
	int f = 1, x = 0;
	char s;
	while (!isdigit(s = nc()))
		if (s == 45) f = -1;
	do {
		x = (x << 1) + (x << 3) + (s ^ 48);
	} while (isdigit(s = nc()));
	*w = x * f;
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
int min(int a, int b) {
	return a < b ? a : b;
}
const int MOD = 1000000007;
int n, m, f[100000001], p[70000001], l, u[100000001], s;
char vis[100000001];
int main() {
	read(&n);
	m = n;
	f[1] = 1;
	for (int i = 2; i <= n; ++i) {
		if (!vis[i]) {
			p[l++] = i;
			u[i] = -1;
		}
		for (int j = 0, k; j < l && (k = i * p[j]) <= n; ++j) {
			vis[k] = 1;
			if (i % p[j]) {
				u[k] = -u[i];
			}
			else {
				u[k] = 0;
				break;
			}
		}
		f[i] = (int)((f[i - 1] + 1ll * i * i * u[i]) % MOD);
	}
	for (int i = 1, j, r, a, b; i <= n; i = j + 1) {
		r = 0;
		a = b = n / i;
		j = min(n / a, m / b);
		for (int x = 1, y; x <= a; x = y + 1) {
			y = min(a / (a / x), b / (b / x));
			r = (r + (1ll * (a / x) * (a / x + 1) / 2 % MOD) * (f[y] - f[x - 1] + MOD) % MOD * (1ll * (b / x) * (b / x + 1) / 2 % MOD)) % MOD;
		}
		s = (s + (1ll * (i + j) * (j - i + 1) / 2) % MOD * r) % MOD;
	}
	write(s);
}