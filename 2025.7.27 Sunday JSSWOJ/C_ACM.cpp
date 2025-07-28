//
// Created by 118 on 25-7-27.
//
#include <stdio.h>
#include <ctype.h>
#ifdef _WIN64
#define getchar_unlocked() _getchar_nolock()
#define putchar_unlocked(_c) _putchar_nolock(_c)
#endif
typedef long long ll;
void read(int* w) {
	int f = 1, x = 0;
	char s = getchar_unlocked();
	while (!isdigit(s)) {
		if (s == 45) f = -f;
		s = getchar_unlocked();
	}
	do {
		x = (x << 1) + (x << 3) + (s ^ 48);
		s = getchar_unlocked();
	} while (isdigit(s));
	*w = x * f;
}
void write(ll x) {
	if (x < 0) {
		x = -x;
		putchar_unlocked(45);
	}
	if (x > 9) write(x / 10);
	putchar_unlocked(x % 10 + 48);
}
ll min(ll a, ll b) {
	return a < b ? a : b;
}
const ll LLMAX = 9223372036854775807ll;
int n, d[3][150001], pref[3][150001], qk[6][3]={{0,1,2}, {0,2,1}, {1,0,2}, {1,2,0}, {2,0,1}, {2,1,0}}, i, j, k;
ll ans = LLMAX, best, cand;
int main() {
	read(&n);
	for (i = 0; i < 3; ++i) {
		for (j = 1; j <= n; ++j) {
			read(&d[i][j]);
			pref[i][j] = pref[i][j - 1] + d[i][j];
		}
	}
	for (i = 0; i < 6; ++i) {
		best = cand = LLMAX;
		for (j = 2; j <= n - 1; ++j){
			k = j - 1;
			best = min(best, pref[qk[i][0]][k] - pref[qk[i][1]][k]);
			cand = min(cand, best + pref[qk[i][1]][j] - pref[qk[i][2]][j]);
		}
		ans = min(ans, pref[qk[i][2]][n] + cand);
	}
	write(ans);
}