#define scanf __builtin_scanf
#define printf __builtin_printf
int n;
char a[20001], b[20001];
int main() {
	scanf("%d%s%s", &n, a, b);
	for (int i = 0; i < n; ++i) {
		if (i == n - 4 || a[i + 4]=='.') {
			printf("v");
			i += 4;
		}
		else {
			printf("w");
			i += 8;
		}
	}
}
