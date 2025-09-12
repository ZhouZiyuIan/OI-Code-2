#pragma GCC optimize(2, 3, "Ofast", "inline")
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MOD 1000000007
int n, a[5001], *child[5001], child_cnt[5001], childSize[5001];
int freq[5001];
long long totEven = 0;
typedef struct {
	long long even;
	long long odd;
} Pair;
Pair dfs_tot(int u) {
	Pair res;
	res.even = 0;
	res.odd = 1;
	int i;
	for (i = 0; i < child_cnt[u]; i++) {
		int v = child[u][i];
		Pair sub = dfs_tot(v);
		long long A = (1 + sub.even) % MOD;
		long long B = sub.odd % MOD;
		long long even_new = ((res.even * A) % MOD + (res.odd * B) % MOD) % MOD;
		long long odd_new = ((res.odd * A) % MOD + (res.even * B) % MOD) % MOD;
		res.even = even_new;
		res.odd = odd_new;
	}
	totEven = (totEven + res.even) % MOD;
	return res;
}
int curCandidate, candTotal;
long long cand_bad_tot = 0;
long long *dfs_bad(int u) {
	int L = 2 * candTotal + 1;
	int offset = candTotal;
	long long *dp = (long long *) calloc(L, sizeof(long long));
	int val = (a[u] == curCandidate) ? 1 : -1;
	dp[offset + val] = 1;
	int i;
	for (i = 0; i < child_cnt[u]; i++) {
		int v = child[u][i];
		long long *child_dp = dfs_bad(v);
		long long *newdp = (long long *) calloc(L, sizeof(long long));
		int x, y;
		for (x = 0; x < L; x++) {
			if (dp[x] == 0) continue;
			newdp[x] = (newdp[x] + dp[x]) % MOD;
			for (y = 0; y < L; y++) {
				if (child_dp[y] == 0) continue;
				int sum_val = (x - offset) + (y - offset);
				if (sum_val >= -candTotal && sum_val <= candTotal) {
					int newIndex = sum_val + offset;
					newdp[newIndex] = (newdp[newIndex] + (dp[x] * child_dp[y]) % MOD) % MOD;
				}
			}
		}
		free(child_dp);
		free(dp);
		dp = newdp;
	}
	for (int jIdx = 0; jIdx < L; jIdx++) {
		int s = jIdx - offset;
		if (s > 0 && (s & 1) == 0) {
			cand_bad_tot = (cand_bad_tot + dp[jIdx]) % MOD;
		}
	}
	return dp;
}
void buildTree() {
	int i;
	for (i = 1; i <= n; i++) {
		child_cnt[i] = 0;
	}
}
int main() {
#ifndef __WIN32
	freopen("tree.in", "r", stdin);
	freopen("tree.out", "w", stdout);
#endif
	int i;
	scanf("%d", &n);
	int *fa = (int *) malloc((n + 1) * sizeof(int));
	fa[1] = 0;
	for (i = 2; i <= n; i++) {
		scanf("%d", &fa[i]);
		child_cnt[fa[i]]++;
	}
	for (i = 1; i <= n; i++) {
		if (child_cnt[i] > 0) {
			child[i] = (int *) malloc(child_cnt[i] * sizeof(int));
			childSize[i] = 0;
		}
		else {
			child[i] = NULL;
			childSize[i] = 0;
		}
	}
	for (i = 2; i <= n; i++) {
		int p = fa[i];
		child[p][childSize[p]++] = i;
	}
	for (i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
		freq[a[i]]++;
	}
	dfs_tot(1);
	int c;
	cand_bad_tot = 0;
	for (c = 1; c <= n; c++) {
		if (freq[c] == 0) {
			continue;
		}
		curCandidate = c;
		candTotal = freq[c];
		long long *dp_root = dfs_bad(1);
		free(dp_root);
	}
	long long ans = (totEven - cand_bad_tot) % MOD;
	if (ans < 0) ans += MOD;
	printf("%lld\n", ans);
	for (i = 1; i <= n; i++) {
		if (child[i] != NULL) {
			free(child[i]);
		}
	}
	free(fa);
}