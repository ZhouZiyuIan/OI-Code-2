#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void solve() {
	int n;
	cin >> n;
	vector<int> a(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}

	vector<vector<int>> dp(n, vector<int>(2, 1));
	// dp[i][0]: length of longest valid subsequence ending at i as a minimum
	// dp[i][1]: length of longest valid subsequence ending at i as a maximum

	int ans = 1;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < i; j++) {
			if (a[i] > a[j]) {
				// a[i] can be the maximum element
				dp[i][1] = max(dp[i][1], dp[j][0] + 1);
			}
			if (a[i] < a[j]) {
				// a[i] can be the minimum element
				dp[i][0] = max(dp[i][0], dp[j][0] + 1);
				dp[i][0] = max(dp[i][0], dp[j][1] + 1);
			}
		}
		ans = max(ans, dp[i][1]);
	}

	cout << ans << "\n";
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int T;
	cin >> T;
	while (T--) {
		solve();
	}

	return 0;
}