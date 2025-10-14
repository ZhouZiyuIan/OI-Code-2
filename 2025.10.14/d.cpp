//
// Created by 118 on 25-10-14.
//
/*
 *不会
 */
#include<bits/stdc++.h>
#define int long long
#define endl "\n"
using namespace std;
const int N=505,mod=998244353;
int n,ret,sum,a[N],b[N];
bool vis[N],gg[N],xr[N];
void dfs(int x){
	if(x==n+1)
	{
		sum++,sum%=mod;
		memset(gg,0,sizeof(gg));
		memset(xr,0,sizeof(xr));
		for(int i=1;i<=n;i++)
		{
			int c=b[i];
			if(gg[a[c]]==0&&xr[a[c]]==1)gg[a[c]]=1;
			else xr[c]=1;
		}
		for(int i=1;i<=n;i++)if(gg[b[i]]==1)ret++,ret%=mod;
		return;
	}
	for(int i=1;i<=n;i++)
	{
		if(vis[i]==1)continue;
		vis[i]=1;
		b[x]=i;
		dfs(x+1);
		vis[i]=0;
	}
}
int ksm(int x,int y,int mod){
	int ret=1;
	while(y!=0)
	{
		if(y%2==1)ret*=x,ret%=mod;
		y/=2;
		x*=x,x%=mod;
	}
	return ret;
}
signed main(){
	freopen("d.in","r",stdin);
	freopen("d.out","w",stdout);
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	dfs(1);
	cout<<ret*ksm(sum,mod-2,mod)%mod;
	return 0;
}
