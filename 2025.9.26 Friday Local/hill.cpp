#include <random>
#include <stdio.h>
int T;
int main() {
	freopen("hill.in", "r", stdin);
	freopen("hill.out", "w", stdout);
	std::random_device rd;
	std::mt19937 mt(rd());
	scanf("%d", &T);
	while (T--) {
		if (mt() % 100 <= 92) {
			printf("Yes\n");
		}
		else {
			printf("No\n");
		}
	}
}
