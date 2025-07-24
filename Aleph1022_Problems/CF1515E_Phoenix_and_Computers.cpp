//
// Created by 118 on 25-7-6.
//
#include<cstdio>
using namespace std;
long long n,M,f[401][401],ans;
int main()
{
    scanf("%lld%lld",&n,&M);
    f[1][1]=1;
    for(int i=2;i<=n;++i)
	{
		for(int j=1;j<=((i+1)/2);++j)
		{
			f[i][j]=(((f[i-1][j]*j%M)*2)%M+f[i-2][j-1]*j%M)%M;
		}
	}
    for(int i=1;i<=((n+1)/2);++i)
	{
		ans=(ans+f[n][i])%M;
	}
    printf("%lld",ans);
    return 0;
}
