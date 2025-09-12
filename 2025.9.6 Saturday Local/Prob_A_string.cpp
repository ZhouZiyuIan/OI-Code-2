//
// Created by 118 on 25-9-6.
//
#include <stdio.h>
int n, ans;
char A[100010], B[100010], tmp;
int main() {
	scanf("%d%s%s", &n, A, B);
	A[n] = '0';
	B[n] = '0';
	for (int i = 0; i < n; ++i) {
		if (A[i] != B[i]) {
			if (A[i] == B[i + 1] && A[i + 1] == B[i]) {
				++ans;
				tmp = A[i];
				A[i] = A[i + 1];
				A[i + 1] = tmp;
			}
			else {
				++ans;
				A[i] = B[i];
			}
		}
	}
	printf("%d", ans);
}