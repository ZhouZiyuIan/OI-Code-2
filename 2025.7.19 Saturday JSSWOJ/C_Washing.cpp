#include <stdio.h>
#include <ctype.h>
#include <map>
#include <vector>
using namespace std;
#ifdef _WIN64
#define getchar_unlocked() _getchar_nolock()
#define putchar_unlocked(_c) _putchar_nolock(_c)
#endif
void read(int *w) {
	int f = 1, x = 0;
	char s = getchar_unlocked();
	while (!isdigit(s)) {
		if (s == '-') {
			f = -f;
		}
		s = getchar_unlocked();
	}
	do {
		x = (x << 1) + (x << 3) + (s ^ 48);
		s = getchar_unlocked();
	}while (isdigit(s));
	x *= f;
	*w = x;
}
void readLL(long long *w) {
	long long f = 1, x = 0;
	char s = getchar_unlocked();
	while (!isdigit(s)) {
		if (s == '-') {
			f = -f;
		}
		s = getchar_unlocked();
	}
	do {
		x = (x << 1) + (x << 3) + (s ^ 48);
		s = getchar_unlocked();
	}while (isdigit(s));
	x *= f;
	*w = x;
}
void write(long long x) {
	if (x < 0) {
		x = -x;
		putchar_unlocked(45);
	}
	if (x > 9) {
		write(x / 10);
	}
	putchar_unlocked(x % 10 + 48);
}
int T, n;
long long K, a[351], ans;
vector<long long>cur(351);
map<vector<long long>, bool>vis;
void dfs(int time) {
	if (time == K) {
		if (!vis[cur]) {
			++ans;
			// for (int i = 0; i < n ; ++i) {
			// 	write(cur[i]);
			// 	putchar_unlocked(32);
			// }
			// putchar_unlocked(10);
			vis[cur] = true;
		}
		return;
	}
	dfs(time + 1);
	for (int i = 0; i < n; ++i) {
		cur[i] >>= 1;
	}
	dfs(time + 1);
	bool f = 0;
	for (int i = 0; i < n; ++i) {
		cur[i] <<= 1;
		if (cur[i] <= 0)f = 1;
		if (!f)--cur[i];
	}
	dfs(time + 1);
	for (int i = 0; i < n; ++i) {
		++cur[i];
	}
}
int main() {
	#ifndef _WIN64
	freopen("wash.in", "r", stdin);
	freopen("wash.out", "w", stdout);
	#endif
	read(&T);
	while (T--) {
		vis.clear();
		read(&n);
		readLL(&K);
		ans = 0;
		for (int i = 0; i < n; ++i) {
			readLL(&a[i]);
			cur[i] = a[i];
		}
		dfs(0);
		write(ans);
		putchar_unlocked(10);
	}
}