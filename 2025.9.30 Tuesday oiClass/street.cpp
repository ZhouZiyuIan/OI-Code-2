#include <stdio.h>

#define MAXN 100005
#define MAXM 200005   // 边数上界，根据题目需要调整

int e[MAXN][MAXN]; // 如果每个点的出度很大，这样会爆内存
// 更合理的写法是用邻接表：
int adj[MAXM], nxt[MAXM], head[MAXN], deg[MAXN];
int tot;

int instack[MAXN];
int ed[MAXN];
int s[MAXN], stop;

int n;

int dfs(int p) {
	if (ed[p]) return 0;
	instack[p] = 1;
	for (;;) {
		if (head[p] == -1) {
			ed[p] = p;
			break;
		}
		int v = adj[head[p]];
		head[p] = nxt[head[p]]; // pop front

		if (instack[v]) {
			stop = 0;
			s[stop++] = p;
			instack[p] = 0;
			return v;
		}

		int cir = dfs(v);
		if (cir == 0) {
			ed[p] = ed[v];
			break;
		}
		s[stop++] = p;
		if (cir == p) {
			int mxd = 0;
			for (int i = 0; i < stop; i++) {
				// 相当于 e[x].pop()，我们已经在 dfs 时 pop 了
				// 所以这里可以留空
			}
		} else {
			instack[p] = 0;
			return cir;
		}
	}
	instack[p] = 0;
	return 0;
}

void readint(int *x) {
	char ch = getchar();
	while (ch < '0' || ch > '9') ch = getchar();
	*x = 0;
	while (ch >= '0' && ch <= '9') {
		*x = (*x) * 10 + (ch - '0');
		ch = getchar();
	}
}

int main() {
	freopen("travel.in", "r", stdin);
	freopen("travel.out", "w", stdout);

	scanf("%d", &n);
	for (int i = 1; i <= n; i++) head[i] = -1;

	for (int i = 1; i <= n; i++) {
		int k;
		readint(&k);
		while (k--) {
			int c;
			readint(&c);
			if (c == i) continue;
			adj[tot] = c;
			nxt[tot] = head[i];
			head[i] = tot++;
		}
	}

	for (int i = 1; i <= n; i++) {
		dfs(i);
		printf("%d\n", ed[i]);
	}
	return 0;
}
