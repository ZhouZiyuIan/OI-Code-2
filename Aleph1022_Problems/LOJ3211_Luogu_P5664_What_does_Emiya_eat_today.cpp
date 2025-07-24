#include<cstdio>
#include<cstring>
const int MOD=998244353;
long long n,m,a[101][2001],f[101][2001],s[101],g[102][205],sumf,sumg;
int main()
{
	freopen("meal.in","r",stdin);
	freopen("meal.out","w",stdout);
    scanf("%lld%lld",&n,&m);
    for(int i=1;i<=n;++i)for(int j=1;j<=m;++j){
        scanf("%lld",&a[i][j]);
        s[i]+=a[i][j];
        s[i]%=MOD;
    }
    f[0][0]=1;
    for(int i=1;i<=n;++i){
        for(int j=0;j<=i;++j){
            if(j==0){
                f[i][j]=f[i-1][j];
                continue;
            }
            f[i][j]=(f[i-1][j]+f[i-1][j-1]*s[i]%MOD)%MOD;
        }
    }
    for(int i=1;i<=n;++i)sumf=(sumf+f[n][i])%MOD;
    for(int k=1;k<=m;++k){
        memset(g,0,sizeof(g));
        g[0][n]=1;
        for(int i=1;i<=n;++i)for(int j=n-i;j<=n+i;++j)g[i][j]=(g[i-1][j]+(g[i-1][j-1]*a[i][k])%MOD+g[i-1][j+1]*(s[i]-a[i][k]))%MOD;
        for(int i=n+1;i<=(n<<1);++i)sumg=(sumg+g[n][i])%MOD;
    }
    printf("%lld",(sumf-sumg+MOD)%MOD);
    return 0;
}
