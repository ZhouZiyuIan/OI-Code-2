//
// Created by 118 on 25-8-1.
//
#include <stdio.h>
#include <stdlib.h>
typedef struct {
	long long num, las;
}node;
node dp[(1 << 20) + 5];
long long a[21];
int T, n, m;
int cmp(const void *a, const void *b) {
	return (*(long long *)a) > *(long long *)b ? 1 : -1;
}
node get_max(node x, node b, int j) {
	if(b.las <= m) {
		b.las += a[j];
	}
	else {
		b.las = a[j];
		++b.num;
	}
	if(x.num == b.num) {
		if(x.las > b.las) {
			return x;
		}
		return b;
	}
	if(x.num > b.num) {
		return x;
	}
	return b;
}
int main() {
	scanf("%d", &T);
	while(T--) {
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= n; ++i) {
			scanf("%lld", &a[i]);
		}
		if(n == 1) {
			putchar(49);
			putchar(10);
			continue;
		}
		qsort(a + 1, n, sizeof(long long), cmp);
		int S = (1 << (n - 1)) - 1;
		m -= a[n];
		node ans;
		ans.las = ans.num = 0;
		for (int i = 0; i <= S; ++i) {
			dp[i].num = dp[i].las = 0;
		}
		for (int i = 0; i <= S; ++i) {
			for (int j = 0; j < n; ++j) {
				if (i & (1 << j)) {
					dp[i] = get_max(dp[i], dp[i ^ (1 << j)], j + 1);
					ans = get_max(ans, dp[i], n);
				}
			}
		}
		printf("%lld\n", ans.num + 1);
	}
}
