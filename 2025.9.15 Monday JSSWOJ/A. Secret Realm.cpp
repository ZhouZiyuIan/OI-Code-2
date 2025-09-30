//
// Created by 118 on 25-9-15.
//
#ifndef FKZ
#include <stdio.h>
#endif
#define scanf __builtin_scanf
#define printf __builtin_printf
typedef unsigned long long ull;
typedef unsigned __int128 u128;
ull n, m;
u128 mm1;
ull sqrt(ull x) {
	ull l = 0, r = 10000000000ull;
	while (l < r) {
		const ull mid = (l + r + 1) >> 1;
		if ((u128)mid * mid <= (u128)x) {
			l = mid;
		}
		else {
			r = mid - 1;
		}
	}
	return l;
}
int main() {
#ifndef FKZ
	freopen("mijing.in", "r", stdin);
	freopen("mijing.out", "w", stdout);
#endif
	scanf("%lld", &n);
	m = sqrt(n);
	mm1 = (u128)(m) * (u128)(m - 1);
	printf("%lld\n", (long long)(((((mm1 * (u128)(2 * m - 1) / 6) << 1ll) + (mm1 >> 1ll)) + ((u128)m * ((u128)n - (u128)m * (u128)m + 1))) % 998244353));
}