//
// Created by 118 on 25-7-31.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#ifdef _WIN64
#define putchar_unlocked _putchar_nolock
#endif
char buf[1 << 20], *p1 = buf, *p2 = buf;
char nc() {
    if (p1 == p2) {
        p1 = buf;
        p2 = p1 + fread(buf, 1, sizeof(buf), stdin);
        if (p1 == p2) {
            return -1;
        }
        return *p1++;
    }
    return *p1++;
}
void read(int *w) {
    int f = 1, x = 0;
    char s;
    while (!isdigit(s = nc()))
        if (s == '-') f = -1;
    do {
        x = x * 10 + (s - '0');
    } while (isdigit(s = nc()));
    *w = x * f;
}
void write(int x) {
    if (x < 0) {
        x = -x;
        putchar_unlocked(45);
    }
    if (x > 9ll) {
        write(x / 10);
    }
    putchar_unlocked(x % 10 + 48);
}
int n, m, u, v, head[5001], to[20001], nxt[20001], tot = 1, deg[5001], vis[5001], res[5001], ans[5001], cnt, curu, curv, edges[10001][2];
void add(int u, int v) {
    to[++tot] = v;
    nxt[tot] = head[u];
    head[u] = tot;
}
int min(int a, int b) {
    return a < b ? a : b;
}
void dfs(int u) {
    vis[u] = 1;
    res[++cnt] = u;
    int tmp[5001], tcnt = 0;
    for (int i = head[u]; i; i = nxt[i]) {
        int v = to[i];
        if ((u == curu && v == curv) || (u == curv && v == curu)) {
            continue;
        }
        if (!vis[v]) tmp[tcnt++] = v;
    }
    if (tcnt > 1) {
        for (int i = 0; i < tcnt - 1; ++i) {
            for (int j = i + 1; j < tcnt; ++j) {
                if (tmp[i] > tmp[j]) {
                    int t = tmp[i];
                    tmp[i] = tmp[j];
                    tmp[j] = t;
                }
            }
        }
    }
    for (int i = 0; i < tcnt; ++i) {
        dfs(tmp[i]);
    }
}
int chk() {
    for (int i = 1; i <= n; ++i) {
        if (res[i] != ans[i]) {
            return res[i] < ans[i];
        }
    }
    return 0;
}
int main() {
    read(&n);
    read(&m);
    for (int i = 1; i <= m; ++i) {
        read(&u);
        read(&v);
        add(u, v);
        add(v, u);
        edges[i][0] = u;
        edges[i][1] = v;
    }
    if (m == n - 1) {
        cnt = 0;
        memset(vis, 0, sizeof(vis));
        dfs(1);
        for (int i = 1; i <= n; ++i) {
            write(res[i]);
            putchar_unlocked(32);
        }
        return 0;
    }
    memset(ans, 0x3f, sizeof(ans));
    for (int i = 1; i <= m; ++i) {
        curu = edges[i][0];
        curv = edges[i][1];
        cnt = 0;
        memset(vis, 0, sizeof(vis));
        dfs(1);
        if (cnt == n && chk()) {
            for (int i = 1; i <= n; ++i) {
                ans[i] = res[i];
            }
        }
    }
    for (int i = 1; i <= n; ++i) {
        write(ans[i]);
        putchar_unlocked(32);
    }
}