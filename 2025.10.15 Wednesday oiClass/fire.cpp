#include<bits/stdc++.h>
using namespace std;
#define mod 1000000007
int n,k,s[200001],zr[200001],ans;
int qp(int a,int b)
{
	int res=1;
	for(;b;b>>=1)
	{
		if(b&1)res=1ll*res*a%mod;
		a=1ll*a*a%mod;
	}
	return res;
}
signed main()
{
	// freopen("fire.in","r",stdin);
	// freopen("fire.out","w",stdout);
	scanf("%d%d",&n,&k);
	s[0]=1;
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&s[i]);
		zr[i]=zr[i-1];
		if(s[i]==100)
		{
			++zr[i];
			s[i]=s[i-1];
		}
		s[i]=570000004ll*(100-s[i])%mod*s[i-1]%mod;
	}
	for(int i=1;i<=n;i++)(ans+=1ll-1ll*s[min(i+k,n)]*qp(s[max(i-k-1,0)],mod-2)%mod*qp(0,zr[min(i+k,n)]-zr[max(i-k-1,0)])%mod+mod)%=mod;
	printf("%d\n",ans);
	return 0;
}