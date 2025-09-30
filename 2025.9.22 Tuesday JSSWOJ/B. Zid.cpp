#define scanf __builtin_scanf
#define printf __builtin_printf
int n, m, a[510][510], cnt[510], emp, lst;
long long ans;
char c[510][510];
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; ++i) {
		scanf("%s", c[i]);
		for (int j = 0; j < m; ++j) {
			a[i][j] = (c[i][j] == '#');
		}
	}
	for (int l = 0; l < m; ++l) {
		for (int i = 0; i < n; ++i) {
			cnt[i] = 0;
		}
		for (int r = l; r < m; ++r) {
			for (int i = 0; i < n; ++i) {
				cnt[i] += a[i][r];
			}
			emp = 0;
			lst = -1;
			for (int i = 0; i < n; ++i) {
				if (!cnt[i]) {
					ans += ++emp;
				}
				else {
					ans += (lst + 1) * (emp + 1);
					lst = cnt[i] == 1 ? emp : -1;
					emp = 0;
				}
			}
			ans += (lst + 1) * (emp + 1);
		}
	}
	printf("%lld", ans);
}
