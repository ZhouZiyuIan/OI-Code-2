//
// Created by 118 on 25-7-18.
//
#include <stdio.h>
#include <string.h>
typedef long long ll;
ll min(ll a, ll b) {
	return a < b ? a : b;
}
ll max(ll a, ll b) {
	return a > b ? a : b;
}
char s[1000001], t[2100001];
ll ans, lens, lent = 1, R[2100001], llen[2100001], rl[2100001];
void init() {
	scanf("%s", s + 1);
	lens = strlen(s + 1);
	t[0] = 36;
	t[1] = 35;
	for (ll i = 1; i <= lens; ++i) {
		t[++lent] = s[i];
		t[++lent] = 35;
	}
}
void Manacher() {
	ll r = 0, mid = 0;
	for (ll pos = 1; pos <= lent; ++pos) {
		if (pos < r) {
			R[pos] = min(r - pos, R[(mid << 1) - pos]);
		}
		else {
			R[pos] = 1;
		}
		while (t[pos - R[pos]] == t[pos + R[pos]]) {
			++R[pos];
		}
		if (R[pos] + pos > r) {
			r = pos + R[pos];
			mid = pos;
		}
		llen[pos + R[pos] - 1] = max(llen[pos + R[pos] - 1], R[pos] - 1);
		rl[pos - R[pos] + 1] = max(rl[pos - R[pos] + 1], R[pos] - 1);
	}
}
int main() {
	init();
	Manacher();
	for (ll i = 3; i <= lent; i += 2) {
		rl[i] = max(rl[i], rl[i - 2] - 2);
	}
	for (ll i = lent; i >= 3; i -= 2) {
		llen[i] = max(llen[i], llen[i + 2] - 2);
	}
	for (ll i = 3; i <= lent; i += 2) {
		if (rl[i] && llen[i]) {
			ans = max(ans, llen[i] + rl[i]);
		}
	}
	printf("%lld", ans);
}