#pragma GCC optimize(3,"Ofast")
#include <cstdio>
#include <iostream>
using namespace std;
int T, ls, le, rs, re, cnt, hsh, hst;
string s;
int main() {
	freopen("divide.in", "r", stdin);
	freopen("divide.out", "w", stdout);
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> T;
	while(T--) {
		cin >> s;
		cnt = ls = le = 0;
		rs = re = s.size() - 1;
		while(le <= rs){
			hsh = (hsh * base)
			while(s.substr(ls, le - ls + 1) != s.substr(rs, re - rs + 1)) {
				le++;
				rs--;
			}
			le = ls = le + 1;
			rs = re = rs - 1;
			cnt += 2;
		}
		cout << cnt - (rs + 2 <= le ? 1 : 0) << '\n';
	}
}
