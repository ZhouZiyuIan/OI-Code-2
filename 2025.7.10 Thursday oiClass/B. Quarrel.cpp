//
// Created by 118 on 25-7-10.
//
#pragma GCC optimize(3,"Ofast")
#include <stdio.h>
#include <ctype.h>
#ifdef _WIN32
#define getchar_unlocked() _getchar_nolock()
#define putchar_unlocked(_c) _putchar_nolock(_c)
#endif
int n, q, u, v, cnt, nxt[200001], head[100001], to[200001], dfn[100001], dep[100001], dc, st[100001][17], lg[100001];
void read(int *w) {
    int f = 1,x = 0;
    char ch = getchar_unlocked();
    while (!isdigit(ch)) {
        if (ch == '-') f = -f;
        ch = getchar_unlocked();
    }
    do {
        x = (x << 1) + (x << 3) + (ch ^ 48);
        ch = getchar_unlocked();
    }while (isdigit(ch));
    x *= f;
    *w = x;
}
void write(int x) {
    if (x < 0) {
        x = -x;
        putchar_unlocked(45);
    }
    if (x > 9) {
        write(x / 10);
    }
    putchar_unlocked(x % 10 + 48);
}
void add(int u, int v) {
    nxt[++cnt] = head[u];
    head[u] = cnt;
    to[cnt] = v;
}
int dfn_min(int u, int v) {
    return dfn[u] < dfn[v] ? u : v;
}
void dfs(int u, int fa) {
    dfn[u] = ++dc;
    st[0][dfn[u]] = fa;
    dep[u] = dep[fa] + 1;
    for (int i = head[u]; i; i = nxt[i]) {
        if (to[i] != fa) {
            dfs(to[i], u);
        }
    }
}
int main() {
    #ifndef _WIN32
    freopen("choose.in", "r", stdin);
    freopen("choose.out", "w", stdout);
    #endif
    read(&n);
    read(&q);
    for (int i = 1; i < n; ++i) {
        read(&u);
        read(&v);
        add(u,v);
        add(v, u);
    }
    dfs(1, 0);
    for(int i=1;i<=n;i++) {
        lg[i] = lg[i - 1] + (1 << lg[i - 1] == i);
    }
    for (int j = 1; j <= lg[n]; ++j) {
        for (int i = 1; i <= n - (1 << j) + 1; ++i) {
            st[i][j] = dfn_min(st[i][j - 1], st[i + (1 << j - 1)][j - 1]);
        }
    }
    for (int i = 1; i <= n; ++i) {}
}