//
// Created by 118 on 25-7-9.
//
#pragma GCC optimize(3,"Ofast")
#include <cstdio>
#include <cstring>
#include <vector>
#include <cctype>
#ifdef _WIN64
#define getchar_unlocked() _getchar_nolock()
#define putchar_unlocked(_c) _putchar_nolock(_c)
#endif
using namespace std;
vector<int>e[1001];
int N, M, a[200001], b[200001], f1[1001][1001], f2[1001][1001];
bool vis[1001][1001];
void dfs1(int x, int beg, int start) {
	if (vis[start][x]) {
		return;
	}
	vis[start][x] = true;
	for (int i : e[x]) {
		if (!vis[start][i]) {
			f1[start][i] = beg;
			dfs1(i, beg, start);
		}
	}
}
void dfs2(int x, int beg, int start) {
	if (vis[start][x]) {
		return;
	}
	vis[start][x] = true;
	for (int i = e[x].size() - 1; i >= 0; --i) {
		if (!vis[start][e[x][i]]) {
			f2[start][e[x][i]] = beg;
			dfs2(e[x][i], beg, start);
		}
	}
}
void read(int&x) {
	int f=1;
	x=0;
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
}
int main() {
	read(N);
	read(M);
	for (int i = 1; i <= M; ++i) {
		read(a[i]);
		read(b[i]);
		e[a[i]].emplace_back(b[i]);
	}
	for (int i = 1; i <= N; ++i) {
		vis[i][i] = 1;
		for (int j : e[i]) {
			dfs1(j, j, i);
		}
		memset(vis[i], 0, sizeof(vis[i]));
		vis[i][i] = 1;
		for (int j = e[i].size() - 1; j >= 0; --j) {
			dfs2(e[i][j], e[i][j], i);
		}
	}
	for (int i = 1; i <= M; ++i) {
		if (vis[b[i]][a[i]]) {
			if (f1[a[i]][b[i]] != f2[a[i]][b[i]]) {
				putchar_unlocked(115);
				putchar_unlocked(97);
				putchar_unlocked(109);
				putchar_unlocked(101);
			}
			else {
				putchar_unlocked(100);
				putchar_unlocked(105);
				putchar_unlocked(102);
				putchar_unlocked(102); 
				putchar_unlocked(78);
			}
		}
		else {
			if (f1[a[i]][b[i]] == f2[a[i]][b[i]]) {
				putchar_unlocked(115);
				putchar_unlocked(97);
				putchar_unlocked(109);
				putchar_unlocked(101);
			}
			else {
				putchar_unlocked(100);
				putchar_unlocked(105);
				putchar_unlocked(102);
				putchar_unlocked(102);
			}
		}
		putchar_unlocked(10);
	}
}
