//
// Created by 118 on 25-7-28.
//
#pragma GCC optimize(3, "Ofast", "inline")
#include <stdio.h>
#include <ctype.h>
#include <bitset>
using namespace std;
#ifdef _WIN64
#define getchar_unlocked() _getchar_nolock()
#define putchar_unlocked(_c) _putchar_nolock(_c)
#endif
void read(int* w) {
	int f = 1, x = 0;
	char s = getchar_unlocked();
	while (!isdigit(s)) {
		if (s == 45) {
			f = -f;
		}
		s = getchar_unlocked();
	}
	do {
		x = (x << 1) + (x << 3) + (s ^ 48);
		s = getchar_unlocked();
	} while (isdigit(s));
	*w = x * f;
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
char s[1001];
bitset<1001> d[1001], dis[501], xop[1001];
pair<int, int> op_val[1001];
int n, m, Q, cnt, head[1001], x, y, vis[501], curv[1001], tot, op[1001], dcm[1001], q, revs[1001];
typedef struct {
	int to, nxt;
	bitset<1001> val;
} node;
node edg[1001];
bitset<1001> read_bs() {
	scanf("%s", s);
	bitset<1001> bs(s);
	return bs;
}
void add(int u, int v) {
	bitset<1001> w = read_bs();
	edg[++cnt].nxt = head[u];
	edg[cnt].to = v;
	edg[cnt].val = w;
	head[u] = cnt;
	edg[++cnt].nxt = head[v];
	edg[cnt].to = u;
	edg[cnt].val = w;
	head[v] = cnt;
}
void ins(int now, bitset<1001> x) {
	for (int i = 1000; i >= 0; --i) {
		if (!x[i]) continue;
		if (curv[i] < now) {
			swap(curv[i], now);
			swap(x, d[i]);
		}
		if (!now) {
			break;
		}
		x ^= d[i];
	}
}
void dfs(int x) {
	for (int i = head[x]; i; i = edg[i].nxt) {
		if (vis[edg[i].to]) {
			ins(0x3f3f3f3f, dis[x] ^ dis[edg[i].to] ^ edg[i].val);
		}
		else {
			vis[edg[i].to] = 1;
			dis[edg[i].to] = dis[x] ^ edg[i].val;
			dfs(edg[i].to);
		}
	}
}
void que(int now) {
	bitset<1001> res;
	for (int i = 1000; i >= 0; --i) {
		if (curv[i] > now && !res[i]) {
			res ^= d[i];
		}
	}
	int flag = 0;
	for (int i = 999; i >= 0; i--) {
		if (res[i] || flag) {
			putchar_unlocked(48 + res[i]);
			if (res[i]) {
				flag = 1;
			}
		}
	}
	if (!flag) {
		putchar_unlocked(48);
	}
	putchar_unlocked(10);
}
int main() {
	read(&n);
	read(&m);
	read(&Q);
	q = Q + 1;
	for (int i = 1; i <= m; ++i) {
		read(&x);
		read(&y);
		add(x, y);
	}
	dfs(1);
	que(0);
	for (int i = 1; i <= Q; ++i) {
		scanf("%s", s);
		read(&x);
		if (s[1] == 'd') {
			read(&y);
			op[i] = ++tot;
			xop[tot] = (read_bs() ^ dis[x] ^ dis[y]);
			op_val[tot] = make_pair(x, y);
			dcm[tot] = tot;
		}
		else if (s[1] == 'h') {
			revs[dcm[x]] = i;
			op[i] = --q;
			xop[q] = (dis[op_val[x].first] ^ dis[op_val[x].second] ^ read_bs());
			dcm[x] = q;
		}
		else {
			revs[dcm[x]] = i;
		}
	}
	for (int i = 1; i <= Q; ++i) {
		if (!revs[i]) {
			revs[i] = 0x3f3f3f3f;
		}
	}
	for (int i = 1; i <= Q; ++i) {
		if (op[i]) {
			ins(revs[op[i]], xop[op[i]]);
		}
		que(i);
	}
}