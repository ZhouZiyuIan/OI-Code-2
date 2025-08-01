#include <stdio.h>
#include <string.h>
char S[2000001];
long long pref[2000001], T, n, maxval;
int main() {
    scanf("%lld", &T);
    while (T--) {
        scanf("%lld%s", &n, S);
        pref[0] = 0;
        for (long long i = 0; i < n; ++i) {
            pref[i + 1] = pref[i] + ((S[i] == '1') ? 1 : -1);
        }
        maxval = -2e9;
        for (long long pos = 1; pos < n; ++pos) {
            long long l = pref[pos];
            long long r = pref[n] - pref[pos];
            long long newval = l * r;
            if (newval > maxval) {
                maxval = newval;
            }
        }
        printf("%lld\n", maxval);
    }
}
