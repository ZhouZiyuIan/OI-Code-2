//
// Created by 118 on 25-9-5.
//
#include <stdio.h>
#include <string.h>
typedef long long ll;
const int dx[4] = {0, 0, 1, -1}, dy[4] = {1, -1, 0, 0};
struct node {
	int x, y, t, ans;
} a[200003];
int n, q, mp[1003][1003], cnt, vis[1003][1003];
char str[2];
void dfs(const int x, const int y) {
	if (!vis[x][y]) {
		++cnt;
	}
	vis[x][y] = 1;
	for (int i = 0; i < 4; ++i) {
		const int mx = x + dx[i], my = y + dy[i];
		if (mx < 0 || mx > n + 1 || my < 0 || my > n + 1 || vis[mx][my] || (mp[mx][my] != -1 && i != mp[mx][my])) {
			continue;
		}
		dfs(mx, my);
	}
}
int main() {
	scanf("%d%d", &n, &q);
	memset(mp, -1, sizeof(mp));
	for (int i = 1; i <= q; ++i) {
		scanf("%d%d%s", &a[i].x, &a[i].y, str);
		if (str[0] == 'L') {
			a[i].t = 0;
		}
		if (str[0] == 'R') {
			a[i].t = 1;
		}
		if (str[0] == 'U') {
			a[i].t = 2;
		}
		if (str[0] == 'D') {
			a[i].t = 3;
		}
		mp[a[i].x][a[i].y] = a[i].t;
	}
	dfs(0, 0);
	a[q].ans = (n + 2) * (n + 2) - cnt;
	for (int i = q; i > 1; --i) {
		mp[a[i].x][a[i].y] = -1;
		if (!vis[a[i].x][a[i].y]) {
			int flag = 0;
			for (int d = 0; d < 4; ++d) {
				flag |= vis[a[i].x + dx[d]][a[i].y + dy[d]];
			}
			if (flag) {
				dfs(a[i].x, a[i].y);
			}
		}
		a[i - 1].ans = (n + 2) * (n + 2) - cnt;
	}
	for (int i = 1; i <= q; ++i) {
		printf("%d\n", a[i].ans);
	}
}
