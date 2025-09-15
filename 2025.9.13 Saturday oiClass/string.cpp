//
// Created by 118 on 25-9-13.
//
#include <cstdio>
#include <cstring>
#define printf __builtin_printf
#define scanf __builtin_scanf
char X[1000001], Y[1000001];
int T, at, ac[26], cur, sd, pos[1000001], tt;
bool flag[26];
size_t lenX, lenY;
int main() {
#ifndef FKZ
 	freopen("string.in", "r", stdin);
 	freopen("string.out", "w", stdout);
#endif
	scanf("%d", &T);
	while (T--) {
		scanf("%s%s", X, Y);
		lenX = strlen(X);
		lenY = strlen(Y);
		tt = sd = cur = at = 0;
		for (int i = 0; i < 26; ++i) {
			flag[i] = ac[i] = 0;
		}
		for (int i = 0; i < lenX; ++i) {
			if (!flag[X[i] - 97]) {
				++at;
				flag[X[i] - 97] = true;
			}
			++ac[X[i] - 97];
		}
		for (int i = 0; i < lenY; ++i) {
			if (flag[Y[i] - 97]) {
				--at;
				flag[Y[i] - 97] = false;
			}
		}
		if (at < 2) {
			putchar(45);
			putchar(49);
			putchar(10);
			continue;
		}
		for (int i = 0; i < 26 && cur != at && sd < 2; ++i) {
			if (ac[i]) {
				if (flag[i]) {
					if (sd == 1) {
						putchar(i + 97);
						break;
					}
					++cur;
					if (cur == at - 1) {
						if ((ac[i] & 1) == 0) {
							--ac[i];
						}
					}
					if (cur == at) {
						ac[i] = 1;
					}
					if (ac[i] & 1) {
						++sd;
					}
				}
				for (int j = 0; j < ac[i]; ++j) {
					putchar(i + 97);
				}
			}
		}
		putchar(10);
	}
}
