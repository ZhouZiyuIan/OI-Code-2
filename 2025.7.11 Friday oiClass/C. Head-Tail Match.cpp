#include <stdio.h>
#include <iostream>
#include <unordered_map>
#include <algorithm>
using namespace std;
#ifdef _WIN32
#define putchar_unlocked(_c) _putchar_nolock(_c)
#define getchar_unlocked() _getchar_nolock()
#endif
unordered_map <int, unordered_map<int, int> > s;
int n, m, len[100001], rt[100001], idx, u, v, siz[6000001], ch[6000001][4], l, r, lenp, idq[2000001];
string c[100001], p, q;
int main() {
    #ifndef _WIN32
    freopen("match.in", "r", stdin);
    freopen("match.out", "w", stdout);
    #endif
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) {
        cin >> c[i];
    }
    sort(c + 1, c + n + 1);
    for (int i = 1; i <= n; ++i) {
        len[i] = c[i].size() - 1;
        for (int j = 0 ; j <= len[i]; ++j) {
            switch (c[i][j]) {
                case 'A':{
                    s[i][j] = 0;
                    break;
                }
                case 'G':{
                    s[i][j] = 1;
                    break;
                }
                case 'U':{
                    s[i][j] = 2;
                    break;
                }
                default: s[i][j] = 3;
            }
        }
    }
    for (int i = 1; i <= n; ++i) {
        rt[i] = ++idx;
        u = rt[i];
        v = rt[i - 1];
        siz[u] = siz[v] + 1;
        for (int j = len[i]; j >= 0; --j) {
            if (!ch[u][s[i][j]]) {
                ch[u][s[i][j]] = ++idx;
            }
            for (int k = 0; k < 4; ++k) {
                if (k != s[i][j]) {
                    ch[u][k] = ch[v][k];
                }
            }
            u = ch[u][s[i][j]];
            v = ch[v][s[i][j]];
            siz[u] = siz[v] + 1;
        }
        for(int j = 0; j < 4; ++j) {
            ch[u][j] = ch[v][j];
        }
    }
    while (m--){
        cin >> p >> q;
        l = lower_bound(c + 1, c + 1 + n, p) - c;
        p[p.size() - 1]++;
        r = lower_bound(c + 1, c + 1 + n, p) - c - 1;
        p[p.size() - 1]--;
        lenp = p.size();
        for(int i = 0; i < q.size(); ++i) {
            switch (q[i]) {
                case 'A':{
                    idq[i] = 0;
                    break;
                }
                case 'G':{
                    idq[i] = 1;
                    break;
                }
                case 'U':{
                    idq[i] = 2;
                    break;
                }
                default: idq[i] = 3;
            }
        }
        u = rt[r];
        v = rt[l - 1];
        for (int i = q.size() - 1; i >= 0; --i) {
            u = ch[u][idq[i]];
            v = ch[v][idq[i]];
        }
        printf("%d", siz[u] - siz[v]);
        putchar_unlocked(10);
    }
}