#pragma GCC optimize(3, "Ofast" ,"fast-math")
#include <stdio.h>
#include <ctype.h>
#include <math.h>
#ifdef _WIN32
#define getchar_unlocked() _getchar_nolock()
#define putchar_unlocked(_c) _putchar_nolock(_c)
#endif
char s[300001];
int lens;
void write(int x) {
	if (x < 0) {
		x = -x;
		putchar_unlocked(45);
	}
	if (x > 9) {
		write(x / 10);
	}
	putchar_unlocked(x % 10 + 48);
}
int main() {
	#ifndef _WIN32
	freopen("guess.in", "r", stdin);
	freopen("guess.out", "w", stdout);
	#endif
	while ((s[lens] = getchar_unlocked())) {
		if (!isdigit(s[lens])) {
			break;
		}
		lens++;
	}
	if (lens == 1) {
		if(s[0] == 49) {
			putchar_unlocked(49);
		}
		else {
			putchar_unlocked(50);
		}
		return 0;
	}
	--lens;
	for (int x = 3; x <= 50000; ++x) {
		if(floor(x * log10(x)) == lens) {
			write(x);
			return 0;
		}
	}
}