//
// Created by 118 on 25-7-18.
//
#include <stdio.h>
#include <string.h>
int min(int a, int b) {
	return a < b ? a : b;
}
const int MOD = 1e9 + 7;
char s[1000001], t[2100001];
int lens, lent, R[2100001];
long long a[2100001], b[2100001], a1, a2, ll[1000001], rl[1000001], ans;
void init() {
	lens = strlen(s);
	lent = 1;
	t[0] = 36;
	t[1] = 35;
	for (int i = 0; i < lens; ++i) {
		t[++lent] = s[i];
		t[++lent] = 35;
	}
	t[lent + 1] = 45;
}
void manacher() {
	int r = 0, mid = 0;
	for (int pos = 1; pos <= lent; ++pos) {
		R[pos] = r > pos ? min(r - pos, R[(mid << 1) - pos]) : 1;
		while (t[pos - R[pos]] == t[pos + R[pos]]) {
			++R[pos];
		}
		if (R[pos] + pos > r) {
			r = pos + R[pos];
			mid = pos;
		}
	}
}
int main() {
	while (~scanf("%s", s)) {
		init();
		manacher();
		for (int i = 0; i <= lent; ++i) {
			a[i] = 0;
			b[i] = 0;
		}
		for (int i = lent; i >= 1; --i) {
			a[i - R[i] + 1] += i;
			a[i + 1] -= i;
			++b[i - R[i] + 1];
			--b[i + 1];
		}
		a1 = 0;
		a2 = 0;
		for (int i = 1; i <= lent; ++i) {
			a1 += a[i];
			a2 += b[i];
			if ((i & 1) == 0) {
				ll[(i >> 1)] = (a1 - ((a2 * i) >> 1)) % MOD;
			}
		}
		for (int i = 0; i <= lent; ++i) {
			a[i] = 0;
			b[i] = 0;
		}
		for (int i = lent; i >= 1; --i) {
			a[i] += i;
			a[i + R[i]] -= i;
			++b[i];
			--b[i + R[i]];
		}
		a1 = 0;
		a2 = 0;
		for (int i = 1; i <= lent; ++i) {
			a1 += a[i];
			a2 += b[i];
			if ((i & 1) == 0) {
				rl[(i >> 1)] = (a1 - ((a2 * i) >> 1)) % MOD;
			}
		}
		ans = 0;
		for (int i = 2; i <= (lent >> 1); ++i) {
			ans = (ans + ll[i] * rl[i - 1] % MOD) % MOD;
		}
		printf("%lld\n", ans);
	}
}
/*
代码注释：
∵ ~-1 = 0, EOF -> -1
∴ while(~XXXX) -> while(XXXX != EOF)
i & 1 -> i % 2
X >> Y -> X / 2^Y
x << y -> x * 2^y
# 的 ASCII 码是 35
$ 的 ASCII 码是 36
(X % MOD + Y % MOD) % MOD == (X + Y) % MOD
*/