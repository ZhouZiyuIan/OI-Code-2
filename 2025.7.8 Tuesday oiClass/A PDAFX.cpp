#include<bits/stdc++.h>
using namespace std;
const int md = 998244853;
int n, m;
int f[50001][1001], ans;
char s[500001], t[1001][1001];
int main() {
	cin >> n >> m;
	scanf("%s", s + 1);
	for (int i = 1; i <= m; i++) {
		scanf("%s", t[i] + 1);
	}
	f[0][0] = 1;
	for (int i = 1; i <= n; i++) {
		f[i][0] = 1;
		if (s[i] == '*') {
			for (int j = 1; j <= m; j++) {
				long long sum = 0;
				for (int k = 0; k <= strlen(t[j] + 1); k++) {
					sum = (sum + f[i - 1][k]) % md;
					cout << sum << endl;
					f[i][k] += sum;
					f[i][k] %= md;
				}
			}
		} else {
			for (int j = 1; j <= m; j++) {
				for (int k = 1; k <= strlen(t[j] + 1); k++) {
					if (t[i][k] == s[i]) {
						f[i][k] = f[i - 1][k - 1];
					}
				}
			}
		}
		for (int j = 1; j <= m; j++) {
			ans += f[i][strlen(t[j] + 1)];
			ans %= md;
		}
	}
	cout << (ans + md) % md << endl;
}