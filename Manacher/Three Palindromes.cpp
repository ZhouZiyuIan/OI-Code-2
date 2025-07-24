//
// Created by 118 on 25-7-18.
//
#include <stdio.h>
#include <string.h>
int min(int a, int b) {
	return a < b ? a : b;
}
int T, lens, lent, R[42001];
char s[20001], t[42001];
void init() {
	lens = strlen(s);
	lent = 0;
	t[lent++] = 36;
	for (int i = 0; i < lens; ++i) {
		t[lent++] = 35;
		t[lent++] = s[i];
	}
	t[lent++] = 35;
	t[lent] = 64;
}
void manacher() {
	int mx = 0, pos = 0;
	for (int i = 1; i < lent; ++i) {
		R[i] = i < mx ? min(mx - i, R[(pos << 1) - i]) : 1;
		while (t[i - R[i]] == t[i + R[i]]) {
			++R[i];
		}
		if (i + R[i] > mx) {
			mx = i + R[i];
			pos = i;
		}
	}
}
int chk() {
	int vis1[42001], vis2[42001], cnt1 = 0, cnt2 = 0, mid;
	for (int i = 1; i < lent; ++i) {
		if (i - R[i] + 1 == 1 && R[i] - 1 > 0) {
			vis1[cnt1++] = i;
		}
		if (i + R[i] - 1 == lent - 1 && R[i] - 1 > 0) {
			vis2[cnt2++] = i;
		}
	}
	for (int i = 0; i < cnt1; ++i) {
		for (int j = cnt2 - 1; j >= 0; --j) {
			if (vis1[i] + R[vis1[i]] - 1 < vis2[j] - R[vis2[j]] + 1) {
				mid = ((vis1[i] + R[vis1[i]] - 1) + (vis2[j] - R[vis2[j]] + 1)) >> 1;
				if (mid - R[mid] + 1 <= vis1[i] + R[vis1[i]] && R[mid] - 1 > 0) {
					return 1;
				}
			}
		}
	}
	return 0;
}
int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%s", s);
		init();
		manacher();
		puts(chk() ? "Yes" : "No");
	}
}