#pragma GCC optimize(2, 3, "Ofast", "inline", "fast-math")
#include <vector>
#include <cstdint>
#include <cstdio>
#include <iostream>
using namespace std;
struct BigInt {
	static constexpr uint32_t base = 1000000000u;
	vector<uint32_t> d;
	explicit BigInt(uint64_t v = 0) {
		if (v) {
			while (v) {
				d.emplace_back(static_cast<uint32_t>(v % base));
				v /= base;
			}
		}
	}
	bool isZero() const {
		return d.empty();
	}
	static int cmp(const BigInt &a, const BigInt &b) {
		if (a.d.size() != b.d.size()) {
			return a.d.size() < b.d.size() ? -1 : 1;
		}
		for (int i = static_cast<int>(a.d.size()) - 1; i >= 0; --i) {
			if (a.d[i] != b.d[i]) {
				return a.d[i] < b.d[i] ? -1 : 1;
			}
		}
		return 0;
	}
	void mul64(uint64_t m) {
		if (m == 0 || isZero()) {
			d.clear();
			return;
		}
		uint64_t carry = 0;
		for (uint32_t &x: d) {
			const __uint128_t cur = static_cast<__uint128_t>(x) * m + carry;
			x = static_cast<uint32_t>(cur % base);
			carry = static_cast<uint64_t>(cur / base);
		}
		while (carry) {
			d.emplace_back(static_cast<uint32_t>(carry % base));
			carry /= base;
		}
	}
	string to_str() const {
		if (d.empty()) {
			return "0";
		}
		string s = to_string(d.back());
		char buf[16];
		for (int i = static_cast<int>(d.size()) - 2; i >= 0; --i) {
			sprintf(buf, "%09u", d[i]);
			s += buf;
		}
		return s;
	}
};
int n, m, k;
vector<uint32_t> a;
int main() {
#ifndef __WIN32
    freopen("ball.in", "r", stdin);
    freopen("ball.out", "w", stdout);
#endif
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n >> m >> k;
	a.resize(n);
	for (int i = 0; i < n; ++i) {
		cin >> a[i];
	}
	int MASK = 1 << m;
	vector<vector<BigInt> > dp(k + 1, vector<BigInt>(MASK, BigInt(0)));
	vector<BigInt> base0(MASK, BigInt(0));
	base0[0] = BigInt(1);
	dp[0][0] = BigInt(1);
	for (int i = 1; i <= n; ++i) {
		int cur = i % (k + 1), prev = (i - 1) % (k + 1);
		for (int s = 0; s < MASK; ++s) {
			dp[cur][s] = dp[prev][s];
		}
		const vector<BigInt> *from = nullptr;
		if (i - k <= 0) from = &base0;
		else {
			int from_idx = 0;
			from_idx = (i - k) % (k + 1);
			from = &dp[from_idx];
		}
		for (int s = 0; s < MASK; ++s) {
			const BigInt &bas = (*from)[s];
			if (bas.isZero()) {
				continue;
			}
			for (int l = 0; l < m; ++l) {
				if (s & (1 << l)) {
					continue;
				}
				if (a[i - 1] <= static_cast<uint32_t>(l)) {
					continue;
				}
				const int sn = s | (1 << l);
				BigInt t = bas;
				t.mul64(static_cast<uint64_t>(a[i - 1]) - static_cast<uint64_t>(l));
				if (BigInt::cmp(t, dp[cur][sn]) > 0) {
					dp[cur][sn] = move(t);
				}
			}
		}
	}
	int last = n % (k + 1);
	BigInt ans(0);
	for (int s = 0; s < MASK; ++s) {
		if (BigInt::cmp(dp[last][s], ans) > 0) {
			ans = dp[last][s];
		}
	}
	cout << ans.to_str() << "\n";
}