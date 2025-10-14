//
// Created by 118 on 25-10-14.
//
#include <stdio.h>
#include <ctype.h>
#define MOD 998244353
void read(int *w) {
	int fl = 1, s = getchar();
	*w = 0;
	while (!isdigit(s)) {
		if (s == 45) {
			fl = -fl;
		}
		s = getchar();
	}
	do {
		*w = (*w << 1) + (*w << 3) + (s ^ 48);
		s = getchar();
	}
	while (isdigit(s));
	*w *= fl;
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
int T, n, ch, f, sum, ans, flag = 1;
char a[2000001];
int main() {
	freopen("a.in", "r", stdin);
	freopen("a.out", "w", stdout);
	read(&T);
	while (T--) {
		sum = n = 0;
		ans = f = 1;
		while (ch = getchar(), ch == 48 || ch == 49) {
			if (ch != 1) {
				flag = 0;
			}
			a[n++] = (char) ch;
		}
		if (flag) {
			write(1);
			putchar(10);
			continue;
		}
		for (int i = 0; i < n - 1; ++i) {
			sum += f;
			if (sum >= MOD) {
				sum -= MOD;
			}
			if (a[i] == 49) {
				f ^= sum ^= f ^= sum;
			}
			ans += f;
			if (ans >= MOD) {
				ans -= MOD;
			}
		}
		write(ans);
		putchar(10);
	}
}
