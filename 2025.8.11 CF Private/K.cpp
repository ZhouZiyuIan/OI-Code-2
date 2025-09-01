//
// Created by 118 on 25-8-1.
//
#include <iostream>
#include <stdio.h>
using namespace std;
char s[4000001];
int n, Q, sz, ch[4000001][26], cnt[4000001], ed[4000001], buf_len, buf[4000001];
int getid() {
	if (buf_len) {
		return buf[--buf_len];
	}
	return sz++;
}
void change(int p, int v) {
	int f = 0, u = 0, x = 0, y = 0;
	for (int i = 0; i < 10; ++i) {
		if (p + i >= n) {
			ed[u] += v;
			break;
		}
		int c = s[p + i] - 97;
		if (!ch[u][c]) {
			ch[u][c] = getid();
		}
		x = u;
		y = c;
		u = ch[u][c];
		cnt[u] += v;
		if (cnt[u] == 0) {
			ch[x][y] = 0;
			buf[buf_len++] = u;
		}
	}
}

int sol(int p) {
	int u = 0;
	int ret = 0;
	for (int i = 0; i < 10; ++i) {
		if (p + i >= n) {
			break;
		}
		ret += ed[u];
		int c = s[p + i] - 97;
		for (int j = 0; j < c; ++j) {
			if (ch[u][j]) {
				ret += cnt[ch[u][j]];
			}
		}
		u = ch[u][c];
	}
	return ret + 1;
}
int main() {
	freopen("out1.out", "w", stdout);
//	ios :: sync_with_stdio(0);
//	cin.tie(0);
//	cout.tie(0);
	cin >> n >> s;
	sz = 1;
	for (int i = 0; i < n; ++i) {
		change(i, 1);
	}
	cin >> Q;
	int op, x;
	string c;
	while (Q--) {
		cin >> op >> x;
		--x;
		if (op == 1) {
			for (int i = max(0, x - 10 + 1); i <= x; ++i) {
				change(i, -1);
			}
			cin >> c;
			s[x] = c[0];
			for (int i = max(0, x - 10 + 1); i <= x; ++i) {
				change(i, 1);
			}
		}
		else {
			cout << sol(x) << '\n';
		}
	}
}
