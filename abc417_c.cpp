// Problem: C - Distance Indicators
// Contest: AtCoder - AtCoder Beginner Contest 417
// URL: https://atcoder.jp/contests/abc417/tasks/abc417_c
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// Input Type: {"type":"stdin"}
// Output Type: {"type":"stdout"}
// Start Programming Time: 2025-08-02 20:00:09
// By: FkZ
// 
// Powered by CP Editor (https://cpeditor.org)

#include <stdio.h>
#include <unordered_map>
using namespace std;
int n, a[200001];
unordered_map<long long, long long>cnt;
long long ans;
int main(){
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i){
		scanf("%d", &a[i]);
	}
	for(int i = 1; i <= n; ++i){
		ans += cnt[i - a[i]];
		++cnt[i + a[i]];
	}
	printf("%lld", ans);
}
