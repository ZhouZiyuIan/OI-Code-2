#include <stdio.h>
#include <stdlib.h>
int n, num[100001], p[100001], pri[100001], pri_c, fp[100001], f[100001], ans;
typedef struct {
    int p, q;
} point;
point d[100001];
void pre(const int x) {
    for (int i = 2; i <= x; ++i) {
        if (!p[i]) {
            pri[pri_c++] = i;
        }
        for (int j = 0; j < pri_c; ++j) {
            if (i * pri[j] > x) {
                break;
            }
            p[i * pri[j]] = 1;
            if (i % pri[j] == 0) {
                break;
            }
        }
    }
}
int cmp_p(const void *a, const void *b) {
    point *p1 = (point *) a, *p2 = (point *) b;
    if (p1->p == p2->p) {
        return p1->q - p2->q;
    }
    return p1->p - p2->p;
}
int cmp_i(const void *a, const void *b) {
    return *(int *) a - *(int *) b;
}
int lower_bound(int a[], int l, int r, const int key) {
    while (l <= r) {
        const int mid = (l + r) >> 1;
        if (a[mid] >= key) {
            r = mid - 1;
        }
        else {
            l = mid + 1;
        }
    }
    return l;
}
int max(const int a, const int b) {
    return a > b ? a : b;
}
int getf(const int x) {
    if (f[x]) {
        return f[x];
    }
    const int pos = lower_bound(fp, 1, n, x);
    for (int i = pos; i <= n; ++i) {
        if (fp[i] > x) {
            break;
        }
        if (d[i].p == x) {
            f[x] = max(getf(d[i].q) + 1, f[x]);
        }
    }
    return f[x];
}
int main() {
    freopen("chain.in", "r", stdin);
    freopen("chain.out", "w", stdout);
    scanf("%d", &n);
    pre(100000);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &num[i]);
        int x = num[i];
        for (int j = 0; j < pri_c; ++j) {
            if (x % pri[j] == 0) {
                d[i].p = pri[j];
                d[i].q = x / pri[j];
                break;
            }
        }
        fp[i] = d[i].p;
    }
    qsort(d + 1, n, sizeof(point), cmp_p);
    qsort(fp + 1, n, sizeof(int), cmp_i);
    for (int i = 1; i <= n; ++i) {
        f[d[i].p] = max(getf(d[i].q) + 1, f[d[i].p]);
    }
    for (int i = 1; i <= 100000; ++i) {
        ans = max(ans, f[i]);
    }
    printf("%d", ans);
}