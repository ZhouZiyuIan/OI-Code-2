#include <stdio.h>
char s[200005], a[200001], b[200001];
int n, m, k, cnt, T, h[200001], to[200001], nxt[200001];
void add(const int u, const int v) {
	to[++cnt] = v;
	nxt[cnt] = h[u];
	h[u] = cnt;
}
int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d%d%s", &n, &m, &k, s + 1);
		for (int i = 1; i <= n; ++i) {
			h[i] = 0;
		}
		cnt = 0;
		for (int i = 0, u, v; i < m; ++i) {
			scanf("%d%d", &u, &v);
			add(u, v);
		}
		for (int i = 1; i <= n; ++i) {
			a[i] = (s[i] == 'A');
		}
		const int tot = k << 1;
		for (int d = 1; d <= tot; ++d) {
			const int al = (d % 2 == 0);
			for (int i = 1; i <= n; ++i) {
				if (al) {
					char w = 0;
					for (int e = h[i]; e; e = nxt[e]) {
						if (a[to[e]]) {
							w = 1;
							break;
						}
					}
					b[i] = w;
				}
				else {
					char w = 1;
					for (int e = h[i]; e; e = nxt[e]) {
						if (!a[to[e]]) {
							w = 0;
							break;
						}
					}
					b[i] = w;
				}
			}
			for (int i = 1; i <= n; i++) {
				a[i] = b[i];
			}
		}
		puts(a[1] ? "Alice" : "Bob");
	}
}
