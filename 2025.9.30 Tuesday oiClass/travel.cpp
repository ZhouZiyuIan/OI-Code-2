//
// Created by 118 on 25-9-30.
//
#include <stdio.h>
#include <vector>
using namespace std;
#define _U 0x01
#define _L 0x02
#define _D 0x04
#define _C 0x08
#define _P 0x10
#define _S 0x20
#define _X 0x40
#define _SP 0x80
extern unsigned char _ctype[];
#define isdigit(c) ((_ctype+1)[c]&(_D))
unsigned char _ctype[] = {
	0x00,_C,_C,_C,_C,_C,_C,_C,_C,_C,_C | _S,_C | _S,_C | _S,_C | _S,_C | _S,_C,_C,_C,_C,_C,_C,_C,_C,_C,_C,_C,_C,_C,_C,
	_C,_C,_C,_C,_S | _SP,_P,_P,_P,_P,_P,_P,_P,_P,_P,_P,_P,_P,_P,_P,_P,_D,_D,_D,_D,_D,_D,_D,_D,_D,_D,_P,_P,_P,_P,_P,_P,
	_P,_U | _X,_U | _X,_U | _X,_U | _X,_U | _X,_U | _X,_U,_U,_U,_U,_U,_U,_U,_U,_U,_U,_U,_U,_U,_U,_U,_U,_U,_U,_U,_U,_P,
	_P,_P,_P,_P,_P,_L | _X,_L | _X,_L | _X,_L | _X,_L | _X,_L | _X,_L,_L,_L,_L,_L,_L,_L,_L,_L,_L,_L,_L,_L,_L,_L,_L,_L,
	_L,_L,_L,_P,_P,_P,_P,_C, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};
void read(int *w) {
	int f = 1, x = 0;
	char s = getchar();
	while (!isdigit(s)) {
		if (s == 45) {
			f = -f;
		}
		s = getchar();
	}
	do {
		x = (x << 1) + (x << 3) + (s ^ 48);
		s = getchar();
	}
	while (isdigit(s));
	x *= f;
	*w = x;
}
void write(int x) {
	if (x < 0) {
		putchar(45);
		x = -x;
	}
	if (x > 9) {
		write(x / 10);
	}
	putchar((x % 10) ^ 48);
}
int n, k[100001], ans[100001], idx[100001];
vector<vector<int> > d;
vector<int> ed;
int main() {
#ifndef __WIN32
	freopen("travel.in", "r", stdin);
	freopen("travel.out", "w", stdout);
#endif
	read(&n);
	d.reserve(n + 1);
	for (int i = 1; i <= n; ++i) {
		read(&k[i]);
		d[i].reserve(k[i]);
		for (int j = 0; j < k[i]; ++j) {
			read(&d[i][j]);
		}
	}
	for (int s = 1; s <= n; ++s) {
		int v = s;
		ed.clear();
		while (true) {
			if (idx[v] >= k[v]) {
				ans[s] = v;
				break;
			}
			if (idx[v] == 0) {
				ed.emplace_back(v);
			}
			v = d[v][idx[v]++];
		}
		for (const int node: ed) {
			idx[node] = 0;
		}
	}
	for (int i = 1; i <= n; ++i) {
		write(ans[i]);
		putchar('\n');
	}
}