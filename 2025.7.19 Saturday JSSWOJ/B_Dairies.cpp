#include <stdio.h>
#include <ctype.h>
#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;
typedef long long ll;
const ll MOD = 1000000007;
#ifdef _WIN64
#define getchar_unlocked() _getchar_nolock()
#define putchar_unlocked(_c) _putchar_nolock(_c)
#endif
void read(ll *w) {
	ll f = 1, x = 0;
	char s = getchar_unlocked();
	while (!isdigit(s)) {
		if (s == '-') {
			f = -f;
		}
		s = getchar_unlocked();
	}
	do {
		x = (x << 1) + (x << 3) + (s ^ 48);
		s = getchar_unlocked();
	}while (isdigit(s));
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
ll n, m, k, kp[300003], tot, l, r, sub1, sub2, last_ans;
unordered_map<ll, unordered_map<ll, ll>> F, qjsum;
ll xjbbljs(const vector<ll>&a,ll l, ll r) {
	vector<ll> tmp(a.begin() + l - 1, a.begin() + r);
	sort(tmp.begin(), tmp.end());
	ll sum = 0;
	for (unsigned p = 0; p < tmp.size(); p++){
		sum = (sum + tmp[p] % MOD * kp[p + 1] % MOD) % MOD;
	}
	return sum % MOD;
}
int main() {
	#ifndef _WIN64
	freopen("diary.in", "r", stdin);
	freopen("diary.out", "w", stdout);
	#endif
	read(&n);
	read(&m);
	read(&k);
	vector<ll> a(n);
	for (ll i = 0; i < n; ++i) {
		read(&a[i]);
	}
	kp[0] = 1;
	for (ll i = 1; i <= n; ++i) {
		kp[i] = kp[i - 1] * k;
		kp[i] %= MOD;
	}
	for (ll i = 1; i <= n; ++i) {
		for (ll j = i; j <= n; ++j) {
			F[i][j] = xjbbljs(a, i, j);
		}
	}
	for (ll L = n; L >= 1; L--){
		for (ll R = L; R <= n; R++){
			if(L == R) {
				qjsum[L][R] = F[L][R] % MOD;
			}
			else {
				qjsum[L][R] = (qjsum[L][R - 1] + qjsum[L + 1][R] - ((L + 1 <= R) ? qjsum[L + 1][R - 1] : 0) + F[L][R] + MOD) % MOD;
			}
		}
	}
	tot = qjsum[1][n];
	for (int i = 0; i < m; i++){
		read(&l);
		read(&r);
		sub1 = 0;
		sub2 = 0;
		if (l > 1) {
			sub1 = qjsum[1][l - 1];
		}
		if (r < n) {
			sub2 = qjsum[r + 1][n];
		}
		last_ans = tot - sub1 - sub2;
		last_ans += (MOD << 1);
		last_ans %= MOD;
		write(last_ans);
		putchar_unlocked(10);
	}
}