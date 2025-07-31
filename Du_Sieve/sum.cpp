//
// Created by 118 on 25-7-31.
//
#include <stdio.h>
#include <ctype.h>
#include <unordered_map>
using namespace std;
#ifdef _WIN64
#define putchar_unlocked _putchar_nolock
#endif
char buf[1 << 10], *p1 = buf, *p2 = buf;
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
void read(unsigned int *w) {
    unsigned int f = 1, x = 0;
    char s;
    while (!isdigit(s = nc()))
        if (s == '-') f = -1;
    do {
        x = x * 10 + (s - '0');
    } while (isdigit(s = nc()));
    *w = x * f;
}
void write(long long x) {
    if (x < 0) {
        x = -x;
        putchar_unlocked(45);
    }
    if (x > 9ll) {
        write(x / 10);
    }
    putchar_unlocked(x % 10 + 48);
}
unsigned int T, n;
long long mu[2000001], pri[2000001], cur, phi[2000001];
bool vis[2000001];
unordered_map<unsigned int, long long> mp_mu, mp_phi;
void sieve() {
    phi[1] = mu[1] = 1;
    for (unsigned int i = 2; i < 2000001; ++i) {
        if (!vis[i]) {
            pri[++cur] = i;
            phi[i] = i - 1;
            mu[i] = -1;
        }
        for (unsigned int j = 1; j <= cur && i * pri[j] < 2000001; ++j) {
            vis[i * pri[j]] = true;
            if (i % pri[j] == 0) {
                mu[i * pri[j]] = 0;
                phi[i * pri[j]] = phi[i] * pri[j];
                break;
            }
            mu[i * pri[j]] = -mu[i];
            phi[i * pri[j]] = phi[i] * (pri[j] - 1);
        }
    }
    for (unsigned int i = 1; i < 2000001; ++i) {
        mu[i] += mu[i - 1];
        phi[i] += phi[i - 1];
    }
}
long long S_mu(unsigned int x) {
    if (x < 2000001) {
        return mu[x];
    }
    if (mp_mu.count(x)) {
        return mp_mu[x];
    }
    long long ret = 1;
    for (unsigned int i = 2, j; i <= x; i = j + 1) {
        j = x / (x / i);
        ret -= S_mu(x / i) * (j - i + 1);
    }
    return mp_mu[x] = ret;
}
long long S_phi(unsigned int x) {
    if (x < 2000001) {
        return phi[x];
    }
    if (mp_phi.count(x)) {
        return mp_phi[x];
    }
    long long ret = (x & 1) ? (long long)x * ((x + 1) >> 1) : (long long)(x >> 1) * (x + 1);
    for (unsigned int i = 2, j; i <= x; i = j + 1) {
        j = x / (x / i);
        ret -= S_phi(x / i) * (j - i + 1);
    }
    return mp_phi[x] = ret;
}
int main() {
    read(&T);
    sieve();
    while (T--) {
        read(&n);
        write(S_phi(n));
        putchar_unlocked(32);
        write(S_mu(n));
        putchar_unlocked(10);
    }
}