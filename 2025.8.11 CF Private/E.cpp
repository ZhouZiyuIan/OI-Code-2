//
// Created by 118 on 25-8-1.
//
#include <stdio.h>
#include <string.h>
int T, n, f;
__int128_t x, affect[2500], effect;
char s[1000001], inv[1000001];
int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%s", s);
		scanf("%lld", (long long*)&x);
		n = strlen(s);
		effect = 1;
		for (int i = 0; i < n; ++i) {
			inv[i] = s[n - i - 1];
		}
		affect['G'] = affect['D'] = affect['U'] = affect['T'] = 0;
		for (int i = 0; i < n; ++i) {
			if (inv[i] == '+') {
				effect = 1;
				continue;
			}
			affect[inv[i]] += effect;
			effect *= 10;
		}
		f = 0;
		for (int G = 0; G < 10; ++G) {
			for (int D = 0; D < 10; ++D) {
				for (int U = 0; U < 10; ++U) {
					for (int T = 0; T < 10; ++T) {
						if (affect['G'] * G + affect['D'] * D + affect['U'] * U + affect['T'] * T == x) {
							puts("YES");
							printf("%d %d %d %d\n", G, D, U, T);
							f = 1;
							break;
						}
					}
					if (f) {
						break;
					}
				}
				if (f) {
					break;
				}
			}
			if (f) {
				break;
			}
		}
		if (f == 0) {
			puts("NO");
		}
	}
}