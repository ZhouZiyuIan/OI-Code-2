#include <stdio.h>
#include <stdlib.h>
typedef struct {
    long long x, y;
	int id;
} ege;
ege A[1000001];
int cmp1(const void *a, const void *b) {
    const ege *ea = (const ege *)a;
    const ege *eb = (const ege *)b;
    if (ea->x < eb->x) return -1;
    if (ea->x > eb->x) return 1;
    return 0;
}
int n;
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%lld%lld", &A[i].x, &A[i].y);
        A[i].id = i;
    }
    qsort(A + 1, n, sizeof(ege), cmp1);
    for (int i = 1; i < n; ++i) {
        if (A[i].y > A[i + 1].y) {
            printf("No");
            return 0;
        }
    }
    printf("Yes\n");
    for (int i = n; i >= 1; --i) {
        if (A[i].x < A[i].y) {
            printf("%d ", A[i].id);
        }
    }
    for (int i = 1; i <= n; ++i) {
        if (A[i].x > A[i].y) {
            printf("%d ", A[i].id);
        }
    }
}
