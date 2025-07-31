//
// Created by 118 on 25-7-31.
//
#include <stdio.h>
typedef long long ll;
ll p, n, inv2, inv6, phi[4800001], pri[4800001], tot;
char vis[4800001];
struct {
    ll key;
    ll value;
} mp_phi[100000];
int siz = 0;
ll find(ll k) {
    for (int i = 0; i < siz; ++i) {
        if (mp_phi[i].key == k) {
            return mp_phi[i].value;
        }
    }
    return -1;
}
void insert(ll k, ll v) {
    mp_phi[siz].key = k;
    mp_phi[siz].value = v;
    ++siz;
}
ll pow(ll x, ll y, ll p) {
    ll ans = 1;
    for (; y; y >>= 1, x = x * x % p) {
        if (y & 1) {
            ans = ans * x % p;
        }
    }
    return ans;
}
ll pow2(ll x) {
    x %= p;
    return x * x % p;
}
ll g(ll x) {
    x %= p;
    return pow2((x * (1 + x) >> 1) % p);
}
ll get_h(ll x) {
    x %= p;
    return x * (x + 1) % p * (2 * x + 1) % p * inv6 % p;
}
ll min(ll a, ll b) {
    return a < b ? a : b;
}
void init(ll n) {
    phi[1] = 1;
    for (ll i = 2; i <= n; ++i) {
        if (!vis[i]) {
            pri[++tot] = i;
            phi[i] = i - 1;
        }
        for (ll j = 1; j <= tot; ++j) {
            ll tmp = pri[j] * i;
            if (tmp > n) {
                break;
            }
            vis[tmp] = 1;
            if (i % pri[j] == 0) {
                phi[tmp] = (phi[i] * pri[j]) % p;
                break;
            }
            phi[tmp] = (phi[i] * (pri[j] - 1)) % p;
        }
    }
    for (ll i = 1; i <= n; i++) {
        phi[i] = (phi[i] * pow2(i) % p + phi[i - 1]) % p;
    }
    inv2 = pow(2, p - 2, p);
    inv6 = pow(6, p - 2, p);
}
ll S_phi(ll n) {
    if (n <= 4800000) {
        return phi[n];
    }
    ll tmpv = find(n);
    if (tmpv != -1) {
        return tmpv;
    }
    ll tmp = g(n);
    for (ll i = 2, last; i <= n; i = last + 1) {
        last = n / (n / i);
        tmp = (tmp - (get_h(last) - get_h(i - 1)) * S_phi(n / i) % p + p) % p;
    }
    insert(n, tmp);
    return tmp;
}
int main() {
    scanf("%lld%lld", &p, &n);
    init(min(4800000, n));
    ll ans = 0;
    for (ll i = 1, last; i <= n; i = last + 1) {
        last = n / (n / i);
        ans = (ans + g(n / i) * ((S_phi(last) - S_phi(i - 1) + p) % p) % p) % p;
    }
    printf("%lld\n", (ans + p) % p);
}