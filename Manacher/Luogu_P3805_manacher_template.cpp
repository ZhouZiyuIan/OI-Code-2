//
// Created by 118 on 25-7-18.
//
#include <stdio.h>
#include <string.h>
int min(int a, int b) {
	return a < b ? a : b;
}
char s[11000001], t[23000001];
int ans, lens, lent = 1, R[23000001];
void init() {
	scanf("%s", s + 1);
	lens = strlen(s + 1);
	t[lent] = 36;
	for (int i = 1; i <= lens; ++i) {
		t[++lent] = 35;
		t[++lent] = s[i];
	}
	t[++lent] = 35;
	t[++lent] = 64;
}
void Manacher() {
	int r = 0, pos = 1, mid = 0;
	while (pos <= lent) {
		R[pos] = pos <= r ? min(r - pos, R[(mid << 1) - pos]) : 0;
		while (t[pos - (R[pos] + 1)] == t[pos + (R[pos] + 1)]) {
			++R[pos];
		}
		if (R[pos] + pos > r) {
			r = pos + R[pos];
			mid = pos;
		}
		if (R[pos] > ans) {
			ans = R[pos];
		}
		++pos;
	}
}
int main() {
	init();
	Manacher();
	printf("%d", ans);
}