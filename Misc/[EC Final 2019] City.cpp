#include <stdio.h>
int n, m;
long long f, g;
int main() {
    scanf("%d%d", &n, &m);
    f = n + 1;
	g = m + 1;
    for (int a = 1; a <= (n >> 1); ++a) {
        f += (n - (a << 1ll) + 1) << 1ll;
    }
    for (int b = 1; b <= (m >> 1); ++b) {
        g += (m - (b << 1ll) + 1) << 1ll;
    }
    printf("%lld", (f * g - 1ll * (n + 1) * (m + 1)) >> 1ll);
}
