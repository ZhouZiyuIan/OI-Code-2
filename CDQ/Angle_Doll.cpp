//
// Created by 118 on 25-7-29.
//
#pragma GCC optimize(3, "Ofast", "inline")
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#ifdef _WIN64
#define getchar_unlocked() _getchar_nolock()
#define putchar_unlocked(_c) _putchar_nolock(_c)
#endif
void read(int* w) {
    int f = 1, x = 0;
    char s = getchar_unlocked();
    while (!isdigit(s)) {
        if (s == 45) {
            f = -f;
        }
        s = getchar_unlocked();
    }
    do {
        x = (x << 1) + (x << 3) + (s ^ 48);
        s = getchar_unlocked();
    } while (isdigit(s));
    *w = x * f;
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
struct node {
    int op, x, y, p;
} a[1000001], v[1000001], w[1000001];
int ans[1000001], n, m, t, c[1000001];
int lowbit(int x) {
    return x & -x;
}
void add(int x, int val) {
    for (int i = x; i < 1000001; i += lowbit(i)) {
        if (val > c[i]) {
            c[i] = val;
        }
    }
}
int ask(int x) {
    int res = 0;
    for (int i = x; i; i -= lowbit(i)) {
        if (c[i] > res) {
            res = c[i];
        }
    }
    return res ? res : -0x3f3f3f3f;
}
void del(int x) {
    for (int i = x; i < 1000001; i += lowbit(i)) {
        c[i] = 0;
    }
}
void div(int l, int r) {
    if (l == r) {
        return;
    }
    int mid = (l + r) >> 1;
    div(l, mid);
    div(mid + 1, r);
    int i = l, j = mid + 1;
    for (int k = l; k <= r; ++k) {
        if (i <= mid && (j > r || v[i].x <= v[j].x)) {
            if (v[i].op == 1) {
                add(v[i].y, v[i].x + v[i].y);
            }
            w[k] = v[i++];
        }
        else {
            if (v[j].op == 2) {
                int tmp = ask(v[j].y);
                ans[v[j].p] > v[j].x + v[j].y - tmp ? ans[v[j].p] = v[j].x + v[j].y - tmp : 0;
            }
            w[k] = v[j++];
        }
    }
    for (int i = l; i <= mid; ++i) {
        if (v[i].op == 1) {
            del(v[i].y);
        }
    }
    for (int i = l; i <= r; ++i) {
        v[i] = w[i];
    }
}
int main() {
    read(&n);
    read(&m);
    for (int i = 1; i <= n; ++i) {
        a[++t].op = 1;
        a[t].p = 0;
        read(&a[t].x);
        read(&a[t].y);
        ++a[t].x;
        ++a[t].y;
    }
    for (int i = 1; i <= m; ++i) {
        read(&a[++t].op);
        read(&a[t].x);
        read(&a[t].y);
        a[t].p = i;
        ++a[t].x;
        ++a[t].y;
    }
    memset(ans, 0x3f, sizeof(ans));
    for (int fx = 0; fx <= 1; ++fx) {
        for (int fy = 0; fy <= 1; ++fy) {
            for (int i = 1; i <= t; ++i) {
                v[i] = a[i];
                v[i].x = fx ? 1000001 - a[i].x : a[i].x;
                v[i].y = fy ? 1000001 - a[i].y : a[i].y;
            }
            div(1, t);
        }
    }
    for (int i = 1; i <= t; i++) {
        if (a[i].op == 2) {
            write(ans[a[i].p]);
            putchar_unlocked(10);
        }
    }
}