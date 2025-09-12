//
// Created by 118 on 25-9-10.
//
#include <stdio.h>
int T, n, m, a[101][101], flag, lst, val, l, r, mx, mn, nmn;
int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &n, &m);
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				scanf("%d", &a[i][j]);
			}
		}
		for (int i = 0; i < n - 1; ++i) {
			for (int j = i + 1; j < n; ++j) {
				if (a[i][0] > a[j][0]) {
					for (int k = 0; k < m; ++k) {
						const int tmp = a[i][k];
						a[i][k] = a[j][k];
						a[j][k] = tmp;
					}
				}
			}
		}
		flag = 1;
		for (int col = 1; col < m; ++col) {
			lst = 0;
			while (lst < n) {
				val = a[lst][0];
				l = r = lst;
				while (r + 1 < n && a[r + 1][0] == val) {
					++r;
				}
				mx = mn = a[l][col];
				for (int i = l; i <= r; ++i) {
					if (a[i][col] > mx) {
						mx = a[i][col];
					}
					if (a[i][col] < mn) {
						mn = a[i][col];
					}
				}
				if (r + 1 < n) {
					nmn = a[r + 1][col];
					for (int i = r + 1; i < n && a[i][0] == a[r + 1][0]; ++i) {
						if (a[i][col] < nmn) {
							nmn = a[i][col];
						}
					}
					if (mx > nmn) {
						flag = 0;
						break;
					}
				}
				lst = r + 1;
			}
			if (!flag) {
				break;
			}
		}
		puts(flag ? "YES" : "NO");
	}
}