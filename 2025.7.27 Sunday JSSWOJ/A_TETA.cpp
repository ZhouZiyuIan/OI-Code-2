//
// Created by 118 on 25-7-27.
//
#include <stdio.h>
#include <ctype.h>
#ifdef _WIN64
#define getchar_unlocked() _getchar_nolock()
#define putchar_unlocked(_c) _putchar_nolock(_c)
#endif
void read(int* w) {
	int f = 1, x = 0;
	char s = getchar_unlocked();
	while (!isdigit(s)) {
		if (s == 45) f = -f;
		s = getchar_unlocked();
	}
	do {
		x = (x << 1) + (x << 3) + (s ^ 48);
		s = getchar_unlocked();
	} while (isdigit(s));
	*w = x * f;
}
void write(int x) {
	if (x < 0) {
		x = -x;
		putchar_unlocked(45);
	}
	if (x > 9) write(x / 10);
	putchar_unlocked(x % 10 + 48);
}
int k, c[21], x, p1, p2, p3, p4, t, s[21], cnt[21], sg, tot;
int main() {
	read(&k);
	for (int i = 1; i <= k; ++i) {
		read(&c[i]);
	}
	read(&x);
	read(&p1);
	read(&p2);
	read(&p3);
	read(&p4);
	read(&t);
	for (int i = 0; i < t; ++i) {
		read(&s[i]);
		++cnt[s[i]];
	}
	for (; ; ) {
		sg = 0;
		if (cnt[p1]) {
			--cnt[p1];
			sg += c[p1];
		}
		if (cnt[p2]) {
			--cnt[p2];
			sg += c[p2];
		}
		if (cnt[p3]) {
			--cnt[p3];
			sg += c[p3];
		}
		if (cnt[p4]) {
			--cnt[p4];
			sg += c[p4];
		}
		if (sg > x) {
			tot += x;
		}
		else {
			tot += sg;
			break;
		}
	}
	for (int i = 1; i <= k; ++i) {
		tot += cnt[i] * c[i];
	}
	write(tot);
}