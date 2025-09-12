//
// Created by 118 on 25-9-5.
//
#include <vector>
#include <array>
#include <cstring>
#include <cstdio>
using namespace std;
typedef long long ll;
constexpr ll MOD = 1e9 + 7;
ll n, inv[1001], fac[1001], siz[1001], tmp[1001], f[1001][1001];
char ch;
vector<array<int, 2> > vec[1001];
void add(ll &x, const ll y) {
	x = (x + y) % MOD;
}
void dfs(const int x, const int fa) {
	siz[x] = f[x][1] = 1;
	for (auto t: vec[x]) {
		if (t[0] != fa) {
			const int y = t[0];
			dfs(y, x);
			memset(tmp, 0, sizeof(tmp));
			for (int i = 1; i <= siz[x]; ++i) {
				for (int j = 1; j <= siz[y]; ++j) {
					if (!t[1]) {
						add(tmp[i + j], f[x][i] * f[y][j]);
					}
					else {
						add(tmp[i + j], MOD - f[x][i] * f[y][j] % MOD), add(tmp[i], f[x][i] * f[y][j]);
					}
				}
			}
			siz[x] += siz[y];
			memcpy(f[x], tmp, sizeof(f[x]));
		}
	}
	for (int i = 1; i <= n; ++i) {
		f[x][i] = f[x][i] * inv[i] % MOD;
	}
}

void sol() {
	scanf("%lld", &n);
	memset(f, 0, sizeof(f));
	for (int i = 1; i <= n; ++i) {
		vec[i].clear();
	}
	for (int i = 1, x, y; i < n; ++i) {
		scanf("%lld%s%lld", &x, &ch, &y);
		++x;
		++y;
		vec[x].push_back({y, ch == '>'});
		vec[y].push_back({x, ch == '<'});
	}
	dfs(1, 0);
	ll ans = 0;
	for (int i = 1; i <= n; ++i) {
		ans = (ans + f[1][i]) % MOD;
	}
	printf("%lld\n", ans * fac[n] % MOD);
}
int main() {
	int T;
	scanf("%d", &T);
	inv[0] = inv[1] = 1;
	for (int i = 2; i < 1001; ++i) {
		inv[i] = MOD - MOD / i * inv[MOD % i] % MOD;
	}
	for (int i = fac[0] = 1; i < 1001; ++i) {
		fac[i] = fac[i - 1] * i % MOD;
	}
	while (T--) {
		sol();
	}
}
