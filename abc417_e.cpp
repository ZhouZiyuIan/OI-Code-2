#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int T, N, M, X, Y, head[1001], to[100001], nxt[100001], ec, deg[1001], edg[1001][1000], adj_sz[1001], vis[1001], vis2[1001], que[1001];
void add(int u, int v) {
    to[ec] = v;
    nxt[ec] = head[u];
    head[u] = ec++;
}
int chk(int src) {
    int qh = 0, qt = 0;
    que[qt++] = src;
    vis2[src] = 1;
    while (qh < qt) {
        int u = que[qh++];
        if (u == Y) return 1;
        for (int i = 0; i < adj_sz[u]; ++i) {
            int v = edg[u][i];
            if (!vis2[v]) {
                vis2[v] = 1;
                que[qt++] = v;
            }
        }
    }
    return 0;
}
int cmp(const void *a, const void *b) {
    int x = *(int *) a, y = *(int *) b;
    return x - y;
}
int main() {
    scanf("%d", &T);
    while (T--) {
        scanf("%d %d %d %d", &N, &M, &X, &Y);
        ec = 0;
        memset(head, -1, sizeof(int) * (N + 1));
        for (int i = 1; i <= N; ++i) {
            adj_sz[i] = 0;
        }
        for (int i = 0; i < M; ++i) {
            int u, v;
            scanf("%d %d", &u, &v);
            add(u, v);
            add(v, u);
            edg[u][adj_sz[u]++] = v;
            edg[v][adj_sz[v]++] = u;
        }
        for (int i = 1; i <= N; ++i) {
            qsort(edg[i], adj_sz[i], sizeof(int), cmp);
        }
        int path[1001], plen = 0;
        memset(vis, 0, sizeof(int) * (N + 1));
        int u = X;
        path[plen++] = u;
        vis[u] = 1;
        while (u != Y) {
            for (int i = 0; i < adj_sz[u]; ++i) {
                int v = edg[u][i];
                if (vis[v]) {
                    continue;
                }
                memcpy(vis2, vis, sizeof(int) * (N + 1));
                if (chk(v)) {
                    path[plen++] = v;
                    vis[v] = 1;
                    u = v;
                    break;
                }
                for (int j = 0; j < N + 1; ++j) {
                    vis2[j] = 0;
                }
            }
        }
        for (int i = 0; i < plen; ++i) {
            printf("%d ", path[i]);
        }
        putchar('\n');
    }
}
