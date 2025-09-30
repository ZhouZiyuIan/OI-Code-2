#ifndef __WIN32
#include <stdio.h>
#endif
#define scanf __builtin_scanf
#define printf __builtin_printf
int T, d;
unsigned long long res;
char n[1001];
int main() {
#ifndef __WIN32
	freopen("triple.in", "r", stdin);
	freopen("triple.out", "w", stdout);
#endif
	scanf("%d", &T);
	while(T--) {
		scanf("%s", n);
		res = 1;
		for (int i = 0; n[i] != '\0'; ++i) {
			d = n[i] ^ 48;
			res = (res * (d + 2) * (d + 1) / 2);
		}
		printf("%llu\n", res);
	}
}
