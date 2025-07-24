#pragma GCC optimize(3,"Ofast")
#include <stdio.h>
#include <ctype.h>
#include <vector>
#include <algorithm>
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
void write(int x) {
	if (x < 0) {
		x = -x;
		putchar_unlocked(45);
	}
	if (x > 9) {
		write(x / 10);
	}
	putchar_unlocked(x % 10 + 48);
}
vector<int> tree[301][301];
int n, m, q, type, siz[301][301], x1, y1, x2, y2, s, t, last_ans;
int query(int x, int y, int val) {
    int res = 0;
    for(int i = x; i > 0; i -= i & -i) {
        for(int j = y; j > 0; j -= j & -j) {
            res += upper_bound(tree[i][j].begin(), tree[i][j].end(), val) - tree[i][j].begin();
        }
    }
    return res;
}
int get(int x1, int y1, int x2, int y2, int val) {
    return query(x2, y2, val) - query(x1 - 1, y2, val) - query(x2, y1 - 1, val) + query(x1 - 1, y1 - 1, val);
}
int main() {
	#ifndef _WIN64
	freopen("bath.in", "r", stdin);
	freopen("bath.out", "w", stdout);
	#endif
	read(&n);
	read(&m);
	read(&q);
	read(&type);
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			read(&siz[i][j]);
			for (int x = i; x <= n; x += x & -x) {
				for (int y = j; y <= m; y += y & -y) {
					tree[x][y].emplace_back(siz[i][j]);
				}
			}
		}
	}
	for (int i = 1; i <= n; i++){
		for (int j = 1; j <= m; j++){
			sort(tree[i][j].begin(), tree[i][j].end());
		}
	}
	while (q--) {
		read(&x1);
		read(&y1);
		read(&x2);
		read(&y2);
		read(&s);
		read(&t);
		if (type == 1) {
			x1 ^= last_ans;
			y1 ^= last_ans;
			x2 ^= last_ans;
			y2 ^= last_ans;
			s ^= last_ans;
			t ^= last_ans;
		}
		x1 = (x1 - 1 + n) % n + 1;
		x2 = (x2 - 1 + n) % n + 1;
		y1 = (y1 - 1 + m) % m + 1;
		y2 = (y2 - 1 + m) % m + 1;
		if (x1 > x2) swap(x1, x2);
		if (y1 > y2) swap(y1, y2);
		if (s > t) swap(s, t);
		write(last_ans = get(x1, y1, x2, y2, t) - get(x1, y1, x2, y2, s - 1));
		putchar_unlocked(10);
	}
}