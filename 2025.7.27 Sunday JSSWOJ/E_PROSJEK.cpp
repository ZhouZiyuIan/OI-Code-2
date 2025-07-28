//
// Created by 118 on 25-7-27.
//
#include<stdio.h>
double min(double a, double b) {
	return a < b ? a : b;
}
double max(double a, double b) {
	return a > b ? a : b;
}
int n, k;
double mid, diff[300001], sum[300001], a[300001], l = 1e6, r;
int chk(double x) {
    for (int i = 1; i <= n; ++i) {
        diff[i] = a[i] - x;
    }
    for (int i = 1; i <= n; ++i) {
        sum[i] = sum[i - 1] + diff[i];
    }
    double prefmin = 0;
    for (int j = k; j <= n; j++) {
        prefmin = min(prefmin, sum[j - k]);
        if (sum[j] - prefmin >= 0) {
        	return 1;
		}
    }
    return 0;
}
int main() {
	scanf("%d%d", &n, &k);
	for (int i = 1; i <= n; ++i) {
		scanf("%lf", &a[i]);
		l = min(a[i], l);
		r = max(a[i], r);
	}
	for(int i = 0; i < 200; ++i) {
		mid = (l + r) / 2.0;
		if (chk(mid)) {
			l = mid;
		}
		else {
			r = mid;
		}
	}
	printf("%lf", ((long long)(l * 1000000)) / 1000000.0);
}
