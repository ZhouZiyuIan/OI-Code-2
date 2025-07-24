//
// Created by 118 on 25-7-24.
//
#pragma GCC optimize(3,"Ofast")
#include <stdio.h>
double abs(double x) {
	return x < 0 ? -x : x;
}
int n, w;
double b[15][15], a[15][15], tmp;
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n + 1; ++i) {
		for (int j = 1; j <= n; ++j) {
			scanf("%lf", &b[i][j]);
		}
	}
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			a[i][j] = (b[i][j] - b[i + 1][j]) * 2.0;
			a[i][n + 1] += (b[i][j] * b[i][j] - b[i + 1][j] * b[i + 1][j]);
		}
	}
	for (int i = 1; i <= n; ++i) {
		w = i;
		for (int j = i + 1; j <= n; ++j) {
			if (abs(a[j][i]) > abs(a[w][i])) {
				w = j;
			}
		}
		if(w != i) {
			for (int j = i; j <= n + 1; ++j) {
				tmp = a[w][j];
				a[w][j] = a[i][j];
				a[i][j] = tmp;
			}
		}
		for (int k = i + 1; k <= n; ++k) {
			tmp = a[k][i] / a[i][i];
			for (int j = i; j <= n + 1; ++j) {
				a[k][j] -= a[i][j] * tmp;
			}
        }
	}
	for (int i = n; i; --i) {
		for (int j = i + 1; j <= n; ++j) {
			a[i][n + 1] -= a[j][n + 1] * a[i][j];
		}
		a[i][n + 1] /= a[i][i];
	}
	for (int i = 1; i <= n; ++i) {
		printf("%.3lf ",a[i][n + 1]);
	}
}
