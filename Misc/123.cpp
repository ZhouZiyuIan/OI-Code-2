#include <stdio.h>
#include <stdlib.h>
typedef long long ll;
typedef struct {
    ll a, b;
} Info;
static Info arr[500001];
int cmp_info(const void *p1, const void *p2) {
    Info *x = (Info *)p1, Info *y = (Info *)p2;
    if (x->a < y->a) return -1;
    if (x->a > y->a) return 1;
    return 0;
}
int main() {
    int T;
    if (scanf("%d", &T) != 1) return 0;
    while (T--) {
        ll n;
        int m;
        scanf("%lld %d", &n, &m);
        for (int i = 0; i < m; i++) {
            scanf("%lld %lld", &arr[i].a, &arr[i].b);
        }
        // Add starting point (operation 0 ends with value 0)
        arr[m].a = 0;
        arr[m].b = 0;
        m++;

        qsort(arr, m, sizeof(Info), cmp_info);

        int ok = 1;

        // Inconsistent duplicates at the same a -> impossible
        for (int i = 1; i < m; i++) {
            if (arr[i].a == arr[i - 1].a && arr[i].b != arr[i - 1].b) {
                ok = 0;
                break;
            }
        }
        if (!ok) {
            printf("No\n");
            continue;
        }

        // Deduplicate same a
        int new_m = 1;
        for (int i = 1; i < m; i++) {
            if (arr[i].a != arr[new_m - 1].a) {
                arr[new_m++] = arr[i];
            }
        }
        m = new_m;

        for (int i = 1; i < m && ok; i++) {
            ll a1 = arr[i - 1].a, b1 = arr[i - 1].b;
            ll a2 = arr[i].a, b2 = arr[i].b;
            ll d = a2 - a1; // d >= 1 after dedup

            // Reachable set in d steps:
            // - No reset: {b1 + d}
            // - At least one reset: [0 .. d-1]
            if (b2 != b1 + d && b2 > d - 1) {
                ok = 0;
                break;
            }
        }

        printf(ok ? "Yes\n" : "No\n");
    }
    return 0;
}

