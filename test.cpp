#include <stdio.h>
const int MOD = 998244353;
long long n, T, k, f[5000001], fac[5000001], powb2[5000001], Inv[5000001], Ifac[5000001];
int main() {
	scanf("%lld", &T);
	fac[0] = Ifac[0] = Inv[1] = powb2[0] = f[0] = 1;
	f[1] = 0;
	for(int i = 2; i < 5000001; ++i) {
		Inv[i] = Inv[MOD % i] * (MOD - MOD / i) % MOD;
		f[i] = ((f[i - 1] * (i - 1) << 2ll) + (f[i - 2] << 3ll)) % MOD * Inv[i] % MOD;
	}
	for(int i = 1; i < 5000001; ++i) {
		fac[i] = fac[i - 1] * i % MOD;
		Ifac[i] = Ifac[i - 1] * Inv[i] % MOD;
		powb2[i] = (powb2[i - 1] << 1ll) % MOD;
	}
	while(T--) {
		scanf("%lld", &n);
		for (k = 0; k <= n; ++k) {
			printf("%lld\n", fac[n] * fac[n] % MOD * powb2[k] % MOD * Ifac[k] % MOD * f[n - k] % MOD);
		}
	}
}