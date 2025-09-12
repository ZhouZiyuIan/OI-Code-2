//
// Created by 118 on 25-9-10.
//
#include <stdio.h>
const int c[5][5] = {{1}, {1, 1}, {1, 2, 1}};
int a[100010], t, n, ans;
char y;
int lucas(const int n, const int m) {
	return m ? c[n % 3][m % 3] * lucas(n / 3, m / 3) % 3 : 1;
}
int main() {
	scanf("%d", &t);
	while (t--) {
		scanf("%d", &n);
		ans = 0;
		for (int i = 0; i < n; ++i) {
			while (((y = (char)getchar())) && ~y && (y < 'A' || y > 'C')) {}
			a[i] = y - 65;
		}
		for (int i = 0; i < n; ++i) {
			ans = (ans + lucas(n - 1, i) * a[i]) % 3;
		}
		if (n % 2 == 0) {
			ans = (3 - ans) % 3;
		}
		putchar(ans + 65);
		putchar(10);
	}
}