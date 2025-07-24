#pragma GCC optimize(3,"Ofast")
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <vector>
using namespace std;
#ifdef _WIN32
#define getchar_unlocked() _getchar_nolock()
#define putchar_unlocked(_c) _putchar_nolock(_c)
#endif
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
int min(int a, int b) {
    return a < b ? a : b;
}
vector<int>g[1000001];
int n, a[1000001], t, q[1000001], c, A = 0x3f, d[1000001], s, x, p[1000001];
int main() {
	#ifndef _WIN32
	freopen("choose.in", "r", stdin);
	freopen("choose.out", "w", stdout);
	#endif
    read(&n);
    for (int i = 1; i <= n; ++i) {
        read(&a[i]);
    }
    for (int i = 1; i <= n; ++i) {
        t = 0;
        q[2] = 1;
        for (int j = 2; j * j <= a[i]; ++j) {
            c = 0;
            while (a[i] % j == 0) {
                a[i] /= j;
                ++c;
            }
            if (c & 1) {
                q[++t] = j;
            }
        }
        if (a[i] > 1) {
            q[++t] = a[i];
        }
        if (t == 0) {
            A = 1;
        }
        g[q[1]].emplace_back(q[2]);
        g[q[2]].emplace_back(q[1]);
    }
    for (int i = 1; i <= 1000; ++i) {
        for (int j = 1; j < 1000001; ++j) {
            d[j] = 0x3f;
        }
        d[i] = 0;
        s = t = 0;
        q[++t] = i;
        while (s < t) {
            x = q[++s];
            for (int j = 0; j < g[x].size(); ++j) {
                if (g[x][j] != p[x]) {
                    if (d[g[x][j]] == 0x3f) {
                        d[g[x][j]] = d[x] + 1;
                        p[g[x][j]] = x;
                        q[++t] = g[x][j];
                    }
                    else {
                        A = min(A, d[x] + d[g[x][j]] + 1);
                    }
                }
            }
        }
    }
    if (A == 0x3f) {
        putchar_unlocked(45);
        putchar_unlocked(49);
    }
    else {
        write(A);
    }
}