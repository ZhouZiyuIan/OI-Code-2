#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int r, c, m;
	cin >> r >> c >> m;

	struct Event { int t, x, y; };
	vector<Event> ev;
	ev.reserve(m + 1);

	// Sentinel start position at time 0
	ev.push_back({0, 1, 1});
	for (int i = 0; i < m; i++) {
		int t, x, y;
		cin >> t >> x >> y;
		ev.push_back({t, x, y});
	}

	// Sort all events by time
	sort(ev.begin(), ev.end(),
		 [](const Event &a, const Event &b) { return a.t < b.t; });

	int n = ev.size();
	vector<int> dp(n, -1000000000);

	dp[0] = 0;
	int best_old = -1000000000;
	int ptr = 0;
	int answer = 0;
	int maxDist = r + c - 2;

	for (int i = 1; i < n; i++) {
		// Move ptr forward for events too old: they can reach anywhere
		while (ptr < i && ev[i].t - ev[ptr].t > maxDist) {
			best_old = max(best_old, dp[ptr]);
			ptr++;
		}

		// Option 1: come from any old event
		dp[i] = best_old + 1;

		// Option 2: check events in the recent time window
		for (int j = ptr; j < i; j++) {
			int dt = ev[i].t - ev[j].t;
			int dist = abs(ev[i].x - ev[j].x) + abs(ev[i].y - ev[j].y);
			if (dist <= dt) {
				dp[i] = max(dp[i], dp[j] + 1);
			}
		}

		answer = max(answer, dp[i]);
	}

	cout << answer << "\n";
	return 0;
}
