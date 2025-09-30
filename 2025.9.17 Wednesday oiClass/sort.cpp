//
// Created by 118 on 25-9-17.
//
#include <stdio.h>
#include <math.h>
int T, n, p[1000001], pos[1000001], cur, op, cnt, lft;
int main() {
	freopen("sort.in", "r", stdin);
	freopen("sort.out", "w", stdout);
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i) {
			scanf("%d", &p[i]);
			pos[p[i]] = i;
		}
		lft = cnt = 0;
		for (int i = 1; i <= n; ++i) {
			if (pos[i] != i) {
				op = 0;
				cur = pos[i];
				while (cur != i && cur != pos[cur]) {
					++op;
					cur = pos[cur];
				}
				cnt += op / 4;
				op %= 4;
				lft += op;
				cnt += lft / 4;
				lft %= 4;
			}
		}
		printf("%d\n", (int)ceil(sqrt(cnt)));
	}
}