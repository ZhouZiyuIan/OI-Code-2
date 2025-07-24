//
// Created by 118 on 25-7-8.
//
#pragma GCC optimize(2,3,"Ofast","inline","fast-math")
#include<stdio.h>
#include<stdlib.h>
long long max(long long x, long long y) {
    return x > y ? x : y;
}
typedef struct{
    long long u, v, w, nxt;
}edg;
edg e[6001];
long long n, c[3001], u, v, w, head[3001], cnt, fa[3001], white[3001], black[3001], cur, mx=-1;
void add(long long u, long long v, long long w) {
    e[++cnt].u = u;
    e[cnt].v = v;
    e[cnt].w = w;
    e[cnt].nxt = head[u];
    head[u] = cnt;
}
int cmp(const void* a, const void* b) {
    return (((edg*)a)->w - ((edg*)b)->w);
}
long long find(long long x) {
    if (x == fa[x])return x;
    else {
        fa[x] = find(fa[x]);
        return fa[x];
    }
}
void calc() {
    cur = 0;
    for (long long i = 1; i <= cnt; i++) {
        u = e[i].u;
        v = e[i].v;
        u = find(u);
        v = find(v);
        fa[v] = u;
        cur += (white[v] * black[u] + black[v] * white[u]) * e[i].w;
        white[u] += white[v];
        black[u] += black[v];
        white[v] = 0;
        black[v] = 0;
    }
    mx = max(mx, cur);
}
void init() {
    for (long long i = 1; i <= n; ++i) {
        fa[i] = i;
        white[i] = 0;
        black[i] = 0;
        if (c[i]) {
            black[i]++;
        }
        else {
            white[i]++;
        }
    }
}
int main() {
    scanf("%lld",&n);
    for (long long i = 1; i <= n; ++i) {
        scanf("%lld", &c[i]);
        fa[i] = i;
        c[i] ? (black[i] = 1) : (white[i] = 1);
    }
    for (long long i = 1; i < n; ++i) {
        scanf("%lld%lld%lld", &u, &v, &w);
        add(u, v, w);
    }
    qsort(e,cnt+1,sizeof(edg),cmp);
    calc();
    for (long long i = 1; i <= n; ++i) {
        if (c[i]) {
            c[i] = 0;
        }
        else {
            c[i] = 1;
        }
        init();
        calc();
        if (c[i]) {
            c[i] = 0;
        }
        else {
            c[i] = 1;
        }
    }
    printf("%lld", mx);
}