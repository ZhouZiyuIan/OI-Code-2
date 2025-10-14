//
// Created by 118 on 25-10-14.
//
#include <bits/stdc++.h>
using namespace std;

int n,k;
const int mod=1e9+7;
struct Mat{
	int a,b,c,d;
	Mat operator * (Mat r){
		return (Mat){(1ll*a*r.a+1ll*b*r.c)%mod,(1ll*a*r.b+1ll*b*r.d)%mod,(1ll*c*r.a+1ll*d*r.c)%mod,(1ll*c*r.b+1ll*d*r.d)%mod};
	}
	Mat operator + (Mat r){
		return (Mat){(a+r.a)%mod,(b+r.b)%mod,(c+r.c)%mod,(d+r.d)%mod};
	}
};
Mat dp[2007][2007],pw[2007];
string s;
signed main(){
	freopen("b.in" ,"r",stdin );
	freopen("b.out","w",stdout);
	cin>>n>>k;
	cin>>s;
	s=" "+s;
	Mat a=(Mat){1,1,1,0},I=(Mat){1,0,0,1};
	dp[0][0]=I;
	for(int i=1;i<=n;i++){
		if(i==1) pw[i]=a;
		else pw[i]=pw[i-1]*pw[i-1];
		for(int j=0;j<=min(i,k);j++){
			dp[i][j]=dp[i-1][j];
			if(j>0) dp[i][j]=dp[i][j]+dp[i-1][j-1]*pw[i];
		}
	}
	Mat pr=I;
	int cn=0,ans=0;
	for(int i=1;i<=n;i++){
		if(s[i]=='1'){
			if(cn<=k) ans=(ans+(pr*dp[n-i][k-cn]).a)%mod;
			pr=pr*pw[n-i+1];
			cn++;
		}
	}
	if(cn==k) ans=(ans+pr.a)%mod;
	cout<<ans<<endl;
	return 0;
}