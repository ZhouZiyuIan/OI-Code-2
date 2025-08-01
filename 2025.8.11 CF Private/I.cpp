#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
vector<pair<int, int>> deal(const string& S, const string& T) {
	vector<pair<int, int>> qj;
	int n = S.length();
	int m = T.length();
	if (m > n) return qj;
	for (int i = 0; i <= n - m; i++) {
		int match = 1;
		for (int j = 0; j < m; j++) {
			if (S[i + j] != T[j]) {
				match = 0;
				break;
			}
		}
		if (match) {
			qj.emplace_back(i + 1, i + m);
		}
	}
	return qj;
}
int sol(const vector<pair<int, int>>& qj) {
	if (qj.empty()) {
		return 0;
	}
	vector<pair<int, int>> sorted = qj;
	sort(sorted.begin(), sorted.end(),[](const pair<int, int>& a, const pair<int, int>& b) {return a.second < b.second;});
	int cnt = 1;
	int curend = sorted[0].second;
	for (const auto& sgqj : sorted) {
		if (sgqj.first > curend) {
			cnt++;
			curend = sgqj.second;
		}
	}
	return cnt;
}
int t, n, m;
string S, T;
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> t;
	while (t--) {
		cin >> n >> m >> S >> T;
		auto qj = deal(S, T);
		cout << sol(qj) << '\n';
	}
}