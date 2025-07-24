//
// Created by 118 on 25-7-18.
//
#include <stdio.h>
#include <string.h>
int min(int a, int b) {
	return a < b ? a : b;
}
char s[100001], t[210001];
int lent, lens, R[210001];
long long lp[210001], rp[210001], ans;
void init() {
	lens = strlen(s + 1);
	t[lent] = 36;
	for (int i = 1; i <= lens; ++i) {
		t[++lent] = 35;
		t[++lent] = s[i];
	}
	t[++lent] = 35;
	t[++lent] = 64;
}
void Manacher() {
	int r = 0, pos = 1, mid = 0;
	while (pos <= lent) {
		R[pos] = pos < r ? min(r - pos, R[(mid << 1) - pos]) : 1;
		while (t[pos - R[pos]] == t[pos + R[pos]]) {
			++R[pos];
		}
		++lp[pos + 1 >> 1];
		--lp[pos + R[pos] >> 1];
		++rp[(pos - R[pos]) / 2 + 1];
		--rp[pos / 2 + 1];
		if (R[pos] + pos > r) {
			r = pos + R[pos];
			mid = pos;
		}
		++pos;
	}
}
int main() {
	while (scanf("%s", s + 1) != EOF) {
		memset(rp, 0, sizeof(rp));
		memset(lp, 0, sizeof(lp));
		lens=lent=0;
		init();
		Manacher();
		for (int i = 1; i <= lens; ++i) {
			rp[i] += rp[i - 1];
			lp[i] += lp[i - 1];
		}
		lp[0] = 0;
		for (int i = 1; i <= lens; ++i) {
			lp[i] += lp[i - 1];
		}
		ans = 0;
		for (int i = lens; i > 1; --i) {
			ans += lp[i - 1] * rp[i];
		}
		printf("%lld\n", ans);
	}
}
