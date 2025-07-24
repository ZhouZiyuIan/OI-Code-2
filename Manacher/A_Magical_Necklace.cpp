//
// Created by 118 on 25-7-18.
//
#pragma GCC optimize(3, "Ofast")
#include <stdio.h>
#include <string.h>
char s[50001],t[110001];
int lens, lent, R[110001], ans, lst, max, r[110001];
int min(int a, int b) {
	return a < b ? a : b;
}
void init() {
	lens = strlen(s + 1);
	lent = 1; 
	t[0] = 36;
	t[1] = 35;
	for (int i = 1; i <= lens; ++i) {
		t[++lent] = s[i];
		t[++lent] = 35;
	}
	t[lent + 1] = 45;
}
void manacher() {
	int mx = 0, pos = 0;
	for (int i = 1; i <= lent; ++i) {
		R[i] = i < mx ? min(mx - i, R[(pos << 1) - i]) : 1;
		while (t[i - R[i]] == t[i + R[i]]) {
			++R[i];
		}
		if (i + R[i] > mx) {
			mx = i + R[i];
			pos = i;
		}
		r[i - R[i] + 1] = i + R[i] - 1;
	}
	ans = 0;
	lst = max = r[1] + 2;
	for (int i = 1; i <= lent; i += 2) {
		if (i == lst) {
			lst = max;
			++ans;
		}
		max < r[i] + 2 ? max = r[i] + 2 : 0;
	}
	printf("%d\n", ans);
}
int main() {
	while (scanf("%s", s + 1) != EOF) {
		init();
		manacher();
	}
}
