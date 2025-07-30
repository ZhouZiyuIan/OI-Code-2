//
// Created by 118 on 25-7-28.
//
#pragma GCC optimize(3, "Ofast", "inline")
#include <stdio.h>
#include <ctype.h>
#ifdef _WIN64
#define getchar_unlocked() _getchar_nolock()
#define putchar_unlocked(_c) _putchar_nolock(_c)
#endif
typedef long long ll;
void read(ll* w) {
    ll f = 1, x = 0;
    char s = getchar_unlocked();
    while (!isdigit(s)) {
        if (s == 45) f = -f;
        s = getchar_unlocked();
    }
    do {
        x = (x << 1) + (x << 3) + (s ^ 48);
        s = getchar_unlocked();
    } while (isdigit(s));
    *w = x * f;
}
void write(ll x) {
    if (x < 0) {
        x = -x;
        putchar_unlocked(45);
    }
    if (x > 9) write(x / 10);
    putchar_unlocked(x % 10 + 48);
}
ll n, m, x, y, tot, head[1000010], to[5000010], nxt[5000010], cnt, dfn[1000010], low[1000010], sz[1000010], ans[1000010];
void add(ll u, ll v) {
    to[++cnt] = v;
    nxt[cnt] = head[u];
    head[u] = cnt;
}
void dfs(ll u, ll fa) {
    dfn[u] = low[u] = ++tot;
    sz[u] = 1;
    ll res = n - 1;
    ans[u] = res;
    for (ll i = head[u]; i; i = nxt[i]) {
        ll v = to[i];
        if (v == fa) {
            continue;
        }
        if (!dfn[v]) {
            dfs(v, u);
            low[u] = (low[u] < low[v]) ? low[u] : low[v];
            sz[u] += sz[v];
            if (dfn[u] <= low[v]) {
                ans[u] += sz[v] * (n - sz[v]);
                res -= sz[v];
            }
        }
		else {
            low[u] = (low[u] < dfn[v]) ? low[u] : dfn[v];
        }
    }
    ans[u] += res * (n - res);
}
int main() {
    read(&n);
    read(&m);
    for (ll i = 1; i <= m; ++i) {
        read(&x);
        read(&y);
        add(x, y);
        add(y, x);
    }
    dfs(1, 0);
    for (ll i = 1; i <= n; ++i) {
        write(ans[i]);
        putchar_unlocked(10);
    }
}