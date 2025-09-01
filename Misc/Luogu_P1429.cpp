#include<stdio.h>
#include<math.h>
#include<stdlib.h>
typedef struct {
    double x, y;
} node;
node s[200010];
int n;
double ans = (1 << 30) + 0.01;
int cmp(const void *a, const void *b) {
    node *pa = (node*) a;
    node *pb = (node*) b;
    if (pa->x < pb->x) return -1;
    if (pa->x > pb->x) return 1;
    if (pa->y < pb->y) return -1;
    if (pa->y > pb->y) return 1;
    return 0;
}
double dis(node a, node b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}
double min(double a, double b) {
    return a < b ? a : b;
}
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%lf%lf", &s[i].x, &s[i].y);
    }
    qsort(s + 1, n, sizeof(node), cmp);
    for (int i = 1; i < n; ++i) {
        for (int j = 1; j <= 5; ++j) {
            ans = min(ans, dis(s[i], s[i + j]));
        }
    }
    printf("%.4lf", ans);
}
