//
// Created by 118 on 25-8-1.
//
#include <stdio.h>
int T, n, fa, fb, fc;
char s1[1000001], s2[1000001];
int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d%s%s", &n, s1, s2);
		fa = fb = fc = 1;
		for (int i = 0; i < n; ++i) {
			if ((s1[i] == 'a' || s2[i] == 'a') && s1[i] != s2[i]) {
				fa = 0;
			}
			if ((s1[i] == 'b' || s2[i] == 'b') && s1[i] != s2[i]) {
				fb = 0;
			}
			if ((s1[i] == 'c' || s2[i] == 'c') && s1[i] != s2[i]) {
				fc = 0;
			}
		}
		if (fa || fb || fc) {
			puts("YES");
			puts("1");
			if (fa) {
				puts("a");
				continue;
			}
			if (fb) {
				puts("b");
				continue;
			}
			puts("c");
		}
		else {
			puts("NO");
		}
	}
}