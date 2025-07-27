//
// Created by 118 on 25-7-26.
//
#include <stdio.h>
#include <stdbool.h>
long long a, b, dp[20][20], digit[20];
long long dfs(int pos, bool limit, bool lead, int dig, long long sum) {
	long long ans = 0;
	if (pos == 0) {
		return sum;
	}
	if (!limit && lead && ~dp[pos][sum]) {
		return dp[pos][sum];
	}
	int up = limit ? digit[pos] : 9;
	for (int j = 0; j <= up; j++) {
		ans += dfs(pos - 1, (j == up) && limit, lead || j, dig, sum + ((j || lead) && (j == dig)));
	}
	if (!limit && lead) {
		dp[pos][sum] = ans;
	}
	return ans;
}
long long ask(long long x, int d) {
	for (int i = 0; i < 20; ++i) {
		for (int j = 0; j < 20; ++j) {
			dp[i][j] = -1;
		}
	}
	int len = 0;
	while (x) {
		digit[++len] = x % 10;
		x /= 10;
	}
	return dfs(len, 1, 0, d, 0);
}
int main() {
	scanf("%lld%lld", &a, &b);
	for (int i = 0; i <= 9; ++i) {
		printf("%lld ", ask(b, i) - ask(a - 1, i));
	}
}