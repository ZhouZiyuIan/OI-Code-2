//
// Created by 118 on 25-9-12.
//
#ifndef _WIN32
#include <cstdio>
#pragma GCC optimize(3, "Ofast", "unroll-loops")
#endif
#include <cctype>
#include <iostream>
#include <unordered_map>
#define printf __builtin_printf
using namespace std;
unordered_map<string, int> freq;
int n;
unsigned short len_fn[110];
string fn[110];
long long ans;
int main() {
#ifndef _WIN32
	freopen("judge.in", "r", stdin);
	freopen("judge.out", "w", stdout);
#endif
	ios :: sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n;
	getline(cin, fn[0]);
	for (int i = 0; i < n; ++i) {
		getline(cin, fn[i]);
		len_fn[i] = fn[i].size();
		for (int j = 0; j < len_fn[i]; ++j) {
			fn[i][j] = static_cast<char>(tolower(fn[i][j]));
		}
		++freq[fn[i]];
	}
	for(int i = 0; i < n; ++i) {
		const string& s = fn[i];
		for(int pos = 0; pos + 1 < len_fn[i]; ++pos) {
			if(s[pos] == 'i' && s[pos + 1] == 'n') {
				string t1 = s.substr(0, pos) + "out" + s.substr(pos + 2), t2 = s.substr(0, pos) + "ans" + s.substr(pos + 2);
				int c1 = freq.count(t1) ? freq[t1] : 0, c2 = freq.count(t2) ? freq[t2] : 0;
				if(t1 == s) {
					--c1;
				}
				if(t2 == s) {
					--c2;
				}
				ans += c1 + c2;
			}
		}
	}
	printf("%lld\n", ans);
}
