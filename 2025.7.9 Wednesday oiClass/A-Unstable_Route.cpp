//
// Created by 118 on 25-7-9.
//
#include <stdio.h>
#include <queue>
#include <utility>
typedef long long ll;
using namespace std;
ll n, m, s, u, v, c, d, l, cnt, head[1000001], dis[1000001];
struct edg {
    ll nxt, to, c, d;
} e[5000001];
priority_queue <pair <ll, ll> > q;
void add(ll from, ll to, ll c, ll d) {
    e[++cnt].nxt = head[from];
    e[cnt].to = to;
    e[cnt].c = c;
    e[cnt].d = d;
    head[from] = cnt;
}
double calc_time(double t) {
    return t + c + (d * 1.0/ (t + 1.0));
}
ll sf(ll t) {
    double l = t, r = t + 20000001, t1, t2, ret = 9223372036854775ll;
    ll mid1, mid2;
    while (l < r) {
        mid1 = l + (r - l) / 3.0;
        mid2 = r - (r - l) / 3.0;
        t1 = calc_time(mid1);
        t2 = calc_time(mid2);
        if (t1 < t2) {
            r = mid2 - 1;
            ret = min(ret, t1);
        }
        else {
            l = mid1 + 1;
            ret = min(ret, t2);
        }
    }
    return ret;
}
void dijkstra() {
    for(ll i = 1; i <= n; i++) {
        dis[i] = 9223372036854775ll;
    }
    dis[s] = 0;
    q.emplace(0, s);
    while(!q.empty()) {
        ll cur_time = -q.top().first,u = q.top().second;
        q.pop();
        if (u == n) {
            return;
        }
        if(cur_time > dis[u]) {
            continue;
        }
        for(ll i = head[u]; i; i = e[i].nxt) {
            ll v = e[i].to;
            c = e[i].c;
            d = e[i].d;
            ll best_time = sf(cur_time);
            if (best_time < dis[v]) {
                dis[v] = best_time;
                q.emplace(-best_time, v);
            }
        }
    }
}
int main() {
    scanf("%lld%lld",&n, &m);
    s = 1;
    for(ll i = 0; i < m; i++) {
        scanf("%lld%lld%lld%lld", &u, &v, &c, &d);
        add(u, v, c, d);
        add(v, u, c, d);
    }
    dijkstra();
    if (dis[n] == 9223372036854775ll) {
        printf("-1");
    }
    else {
        printf("%lld", dis[n]);
    }
}
