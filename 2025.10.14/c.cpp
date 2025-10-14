//
// Created by 118 on 25-10-14.
//
#include <bits/stdc++.h>
using namespace std;

const int B = 62;
typedef long long ll;
int ps[B + 7][B + 7][B + 7];
ll d[B + 7][B + 7][B + 7];

void work(ll x) {
	int s = 0, z = 0;
	ll dis = 0, nw = 0;
	for (int i = B; i >= 0; i--) {
		if (nw + (1ll << i) + ps[i][s][z] <= x) {
			nw += (1ll << i);
			dis += d[i][s][z];
			z = ps[i][s][z], s++;
		}
	}
	if (nw == x)
		cout << dis - 1 << endl;
	else
		cout << -1 << endl;
}

signed main() {
	freopen("c.in", "r",stdin);
	freopen("c.out", "w",stdout);
	for (int j = 0; j <= B; j++) {
		ps[0][j][0] = max(0, j - 1);
		d[0][j][0] = 1;
		for (int k = 1; k <= B; k++) {
			ps[0][j][k] = k - 1;
			d[0][j][k] = 0;
		}
	}
	for (int i = 1; i <= B; i++) {
		for (int j = 0; j <= B - i; j++) {
			for (int k = 0; k <= B; k++) {
				ps[i][j][k] = ps[i - 1][j + 1][ps[i - 1][j][k]];
				d[i][j][k] = d[i - 1][j + 1][ps[i - 1][j][k]] + d[i - 1][j][k];
			}
		}
	}
	ll x;
	int t;
	cin >> t;
	for (int i = 1; i <= t; i++) {
		cin >> x;
		work(x);
	}
	return 0;
}