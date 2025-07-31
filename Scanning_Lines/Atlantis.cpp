//
// Created by 118 on 25-7-30.
//
#include <stdio.h>
#include <stdlib.h>
typedef struct {
    long long l, r, sum;
} node1;
typedef struct {
    long long x, y1, y2;
    long long flag;
} node2;
node1 tree[1600001];
node2 p[400001];
long long n, lazy[1600001];
long long x_1, y_1, x_2, y_2, s[400001], sum;
long long min(long long a, long long b) {
    return a < b ? a : b;
}
long long max(long long a, long long b) {
    return a > b ? a : b;
}
int cmp(const void *a,const void *b) {
    return *(long long*)a > *(long long*)b ? 1 : -1;
}
int cmp2(const void *a,const void *b) {
    return ((node2*)a) -> x > ((node2*)b) -> x ? 1 : -1;
}
void pushup(long long rt) {
    if (lazy[rt] > 0) {
        tree[rt].sum = tree[rt].r - tree[rt].l;
    }
    else {
        tree[rt].sum = tree[rt << 1].sum + tree[rt << 1 | 1].sum;
    }
}
void build(long long rt, long long l, long long r) {
    if (r - l > 1) {
        tree[rt].l = s[l];
        tree[rt].r = s[r];
        build(rt << 1, l, (l + r) >> 1);
        build(rt << 1 | 1, (l + r) >> 1, r);
        pushup(rt);
    }
    else {
        tree[rt].l = s[l];
        tree[rt].r = s[r];
        tree[rt].sum = 0;
    }
}
void update(long long rt, long long y1, long long y2, long long flag) {
    if (tree[rt].l == y1 && tree[rt].r == y2) {
        lazy[rt] += flag;
        pushup(rt);
        return;
    }
    if (tree[rt << 1].r > y1) {
        update(rt << 1, y1, min(tree[rt << 1].r, y2), flag);
    }
    if (tree[rt << 1 | 1].l < y2) {
        update(rt << 1 | 1, max(tree[rt << 1 | 1].l, y1), y2, flag);
    }
    pushup(rt);
}
int main() {
    scanf("%lld", &n);
    for (long long i = 0; i < n; ++i) {
        scanf("%lld%lld%lld%lld", &x_1, &y_1, &x_2, &y_2);
        p[i].x = x_1;
        p[i].y1 = y_1;
        p[i].y2 = y_2;
        p[i].flag = 1;
        p[i + n].x = x_2;
        p[i + n].y1 = y_1;
        p[i + n].y2 = y_2;
        p[i + n].flag = -1;
        s[i + 1] = y_1;
        s[i + n + 1] = y_2;
    }
    qsort(s + 1, n << 1, sizeof(long long), cmp);
    qsort(p, n << 1, sizeof(node2), cmp2);
    build(1, 1, n << 1);
    update(1, p[0].y1, p[0].y2, p[0].flag);
    for (long long i = 1; i < (n << 1); ++i) {
        sum += (p[i].x - p[i - 1].x) * tree[1].sum;
        update(1, p[i].y1, p[i].y2, p[i].flag);
    }
    printf("%lld", sum);
}