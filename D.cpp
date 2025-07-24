#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;
const int N=5e5+10;
ll a[N],n,b[N],m,ans;
bool cmp(ll a,ll b){
	return a>b;
}
int main(){
	scanf("%lld %lld",&n,&m);
	for(int i=1;i<=n;i++)scanf("%lld",a+i);
	sort(a+1,a+1+n);
	for(int i=1;i<n;i++)b[i]=a[i+1]-a[i],ans+=b[i];
	sort(b+1,b+n,cmp);
	printf("%lld\n",ans);
	for(int i=1;i<m;i++)ans-=b[i];
	return 0;
}