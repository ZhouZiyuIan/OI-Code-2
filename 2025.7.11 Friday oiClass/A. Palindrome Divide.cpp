#include <stdio.h>
const int MOD = 998244353;
int T, ls, le, rs, re, cnt;
long long hsh, hst, baset, base = 131;
char s[1000001];
int main() {
	#ifndef _WIN32
	freopen("divide.in", "r", stdin);
	freopen("divide.out", "w", stdout);
	#endif
	scanf("%d", &T);
	while(T--) {
		scanf("%s", s);
		hsh = hst = cnt = ls = le = 0;
		baset = 1;
		for(re = 0; s[re]; ++re);
		re--;
		rs = re;
		while(le <= rs) {
			hsh = (hsh * base + s[le]) % MOD;
			hst = (hst + s[rs] * baset) % MOD;
			baset *= base;
			baset %= MOD;
			while(hsh != hst) {
				le++;
				rs--;
				hsh = (hsh * base + s[le]) % MOD;
				hst = (hst + s[rs] * baset) % MOD;
				baset *= base;
				baset %= MOD;
			}
			le++;
			ls = le;
			rs--;
			re = rs;
			cnt += 2;
			hsh = hst = 0;
			baset = 1;
		}
		printf("%d\n", cnt - (rs + 2 <= le ? 1 : 0));
	}
}
