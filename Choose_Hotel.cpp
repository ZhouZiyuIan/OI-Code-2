//  #2597. 「NOIP2011」选择客栈
#include <stdio.h>
int c, q;
long long n, k, p, o, r, e[2000001], a[2000001], t[2000001];
int main() {
    scanf("%lld%lld%lld", &n, &k, &p);
    for (int i = 1; i <= n; ++i) {
        scanf("%d%d", &c, &q);
        if (q <= p) {
            o = i;
        }
        if (o >= e[c]) {
            a[c] = t[c];
        }
        r += a[c];
        e[c] = i;
        ++t[c];
    }
    printf("%lld", r);
}