//
// Created by 118 on 25-8-1.
//
#include <stdio.h>
int n, a[500001], ans;
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &a[i]);
	}
	for (int i = 1; i <= n; ++i){
		int ava = 1;
		for (int j = 1; j <= i; ++j){
			for (int k = j; k <= n; k += i){
				int rem = a[k] % i;
				if(rem == 0) {
					rem = i;
				}
				if(rem != j){
					ava = 0;
					break;
				}
			}
			if(!ava) {
				break;
			}
		}
		if(ava) {
			++ans;
		}
	}
	printf("%d", ans);
}