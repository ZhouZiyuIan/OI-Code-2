#include<stdio.h>
const int MOD=924844033;
int n,k;
long long fac[2001]={1},t,a[4001]={1},f[4001][2001],ans;
int main(){
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;++i)fac[i]=(fac[i-1]*i)%MOD;
	for(int i=1;i<=(n-k)%k;++i){
		a[t+=(n-k)/k+1]=1;
		a[t+=(n-k)/k+1]=1;
	}
	for(int i=1;i<=k-(n-k)%k;++i){
		a[t+=(n-k)/k]=1;
		a[t+=(n-k)/k]=1;
	}
	f[0][0]=1;
	for(int i=1;i<=t;++i)for(int j=0;j<=n;++j){
		f[i][j]=f[i-1][j];
		if(j)f[i][j]+=f[i-1-(!a[i-1])][j-1];
		f[i][j]%=MOD;
	}
	for(int i=0;i<=n;++i)ans=(ans+f[t][i]*fac[n-i]%MOD*(i&1?MOD-1:1)%MOD)%MOD;
	printf("%lld",ans);
}
