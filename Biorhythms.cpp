//  #10217. 「一本通 6.4 练习 3」Biorhythms

#include <stdio.h>
long long p, e, i, d, T;
int main() {
    while (scanf("%lld%lld%lld%lld", &p, &e, &i, &d) && ~p) {
	    printf("Case %lld: the next triple peak occurs in %lld days.\n", ++T, (((5544 * p + 14421 * e + 1288 * i) % 21252 - d - 1) % 21252 + 21252) % 21252 + 1);
    }
}