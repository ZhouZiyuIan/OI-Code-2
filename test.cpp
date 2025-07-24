#include<bits/stdc++.h>
using namespace std;
#define il inline
#define re register
#define inf 123456789
il int read()
{
    re int x = 0, f = 1; re char c = getchar();
    while(c < '0' || c > '9') { if(c == '-') f = -1; c = getchar();}
    while(c >= '0' && c <= '9') x = x * 10 + c - 48, c = getchar();
    return x * f;
}
#define rep(i, s, t) for(re int i = s; i <= t; ++ i)
#define drep(i, s, t) for(re int i = t; i >= s; -- i)
#define Next(i, u) for(re int i = head[u]; i; i = e[i].next)
#define mem(k, p) memset(k, p, sizeof(k))
#define maxn 1200005
struct edge{int v, w, next;}e[maxn << 1];
int n, m, head[maxn], cnt, k, ans;
int dp[maxn], vis[maxn], sum, dis[maxn], rt, size[maxn], rev[maxn], tot;
il void add(int u, int v, int w)
{
    e[++ cnt] = (edge){v, w, head[u]}, head[u] = cnt;
    e[++ cnt] = (edge){u, w, head[v]}, head[v] = cnt;
}
il void getrt(int u, int fr)
{
    size[u] = 1, dp[u] = 0;
    Next(i, u)
    {
        int v = e[i].v;
        if(v == fr || vis[v]) continue;
        getrt(v, u);
        size[u] += size[v], dp[u] = max(dp[u], size[v]);
    }
    dp[u] = max(dp[u], sum - size[u]);
    if(dp[u] < dp[rt]) rt = u;
}
il void getdis(int u, int fr)
{
    rev[++ tot] = dis[u];
    Next(i, u)
    {
        int v = e[i].v;
        if(v == fr || vis[v]) continue;
        dis[v] = dis[u] + e[i].w;
        getdis(v, u);
    }
}
il int doit(int u, int w)
{
    tot = 0, dis[u] = w, getdis(u, 0);
    sort(rev + 1, rev + tot + 1);
    int l = 1, r = tot, ans = 0;
    while(l <= r) (rev[l] + rev[r] <= k) ? (ans += r - l, ++ l) : (-- r);
    return ans;
}
il void solve(int u)
{
    vis[u] = 1, ans += doit(u, 0);
    Next(i, u)
    {
        int v = e[i].v;
        if(vis[v]) continue;
        ans -= doit(v, e[i].w);
        sum = size[v], dp[0] = n, rt = 0;
        getrt(v, u), solve(rt);
    }
}
int main()
{
    n = read();
    k = read();
    rep(i, 1, n - 1){int u = read(), v = read(), w = read(); add(u, v, w);}
    dp[0] = sum = n, getrt(1, 0), solve(rt);
    printf("%d", ans);
    return 0;
}