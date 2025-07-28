#include <stdio.h>

#define MAXN 500005
#define MOD 1000000000

typedef long long ll;

int a[MAXN];
int n;

// 单调栈（下标栈）
int min_stk[MAXN], max_stk[MAXN];
int min_top = 0, max_top = 0;

ll result = 0;

int min_pos[MAXN], max_pos[MAXN];

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) scanf("%d", &a[i]);

    int l = 0;
    min_top = max_top = 0;

    for (int r = 0; r < n; r++) {
        // 更新 min 栈
        while (min_top > 0 && a[min_stk[min_top - 1]] >= a[r]) min_top--;
        min_pos[r] = min_top == 0 ? 0 : min_stk[min_top - 1] + 1;
        min_stk[min_top++] = r;

        // 更新 max 栈
        while (max_top > 0 && a[max_stk[max_top - 1]] <= a[r]) max_top--;
        max_pos[r] = max_top == 0 ? 0 : max_stk[max_top - 1] + 1;
        max_stk[max_top++] = r;

        int left = l;
        if (min_pos[r] > left) left = min_pos[r];
        if (max_pos[r] > left) left = max_pos[r];

        // 枚举合法 l ∈ [left, r]
        for (int i = r; i >= left; i--) {
            int len = r - i + 1;

            // 找区间 [i..r] 的 min/max
            int minv = a[i], maxv = a[i];
            for (int j = i + 1; j <= r; j++) {
                if (a[j] < minv) minv = a[j];
                if (a[j] > maxv) maxv = a[j];
            }

            ll term = 1LL * len * minv % MOD * maxv % MOD;
            result = (result + term) % MOD;
        }
    }

    printf("%lld\n", result);
    return 0;
}
