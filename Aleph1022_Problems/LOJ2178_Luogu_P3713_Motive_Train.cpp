#include<stdio.h>
#include<string.h>
const int MOD=1e9+9;
int m,n,ans,g[6][6][6][6],ax[6],ay[6],ap[6],aq[6],len1,len2,f[31][31][31][31];
char s[31][31];
int dp(int x,int y,int r,int c){
	if(s[x][y]!=s[r][c])return 0;
	if(x<1||x>m||y<1||y>n||r<1||r>m||c<1||c>n)return 0;
	if(~f[x][y][r][c])return f[x][y][r][c];
	int res=1;
	for(int i=1;i<=len1;++i)for(int j=1;j<=len2;++j)res=(res+dp(x+ax[i],y+ay[i],r+ap[j],c+aq[j]))%MOD;
	return f[x][y][r][c]=res;
}
int dfs(int x,int y,int p,int q){
	if(~g[x+1][y+1][p+1][q+1])return g[x+1][y+1][p+1][q+1];
	len1=len2=0;
	for(int i=-1;i<=1;++i)if(!i||i==x)for(int j=-1;j<=1;++j)if((i||j)&&(!j||j==y)){
		ax[++len1]=i;
		ay[len1]=j;
	}
	for(int i=-1;i<=1;++i)if(!i||i==p)for(int j=-1;j<=1;++j)if((i||j)&&(!j||j==q)){
		ap[++len2]=i;
		aq[len2]=j;
	}
	memset(f,-1,sizeof(f));
	int res=0;
	for(int i=1;i<=m;i++)for(int j=1;j<=n;j++)for(int r=1;r<=m;r++)for(int c=1;c<=n;c++)res=(res+dp(i,j,r,c))%MOD;
	return g[-x+1][-y+1][-p+1][-q+1]=g[-p+1][-q+1][-x+1][-y+1]=g[x+1][y+1][p+1][q+1]=g[p+1][q+1][x+1][y+1]=res;
}
int calc(int x,int y){
	int ret=0;
	ret=dfs(x,y,1,1)%MOD;
	ret=(ret+dfs(x,y,1,-1))%MOD;
	ret=(ret+dfs(x,y,-1,1))%MOD;
	ret=(ret+dfs(x,y,-1,-1))%MOD;
	ret=(ret-dfs(x,y,1,0)+MOD)%MOD;
	ret=(ret-dfs(x,y,-1,0)+MOD)%MOD;
	ret=(ret-dfs(x,y,0,1)+MOD)%MOD;
	ret=(ret-dfs(x,y,0,-1)+MOD)%MOD;
	return ret;
}
int main(){
	memset(g,-1,sizeof(g));
	scanf("%d%d",&m,&n);
	for(int i=1;i<=m;++i)scanf("%s",s[i]+1);
	ans=(ans+calc(1,1))%MOD;
	ans=(ans+calc(1,-1))%MOD;
	ans=(ans+calc(-1,1))%MOD;
	ans=(ans+calc(-1,-1))%MOD;
	ans=(ans-calc(1,0)+MOD)%MOD;
	ans=(ans-calc(-1,0)+MOD)%MOD;
	ans=(ans-calc(0,1)+MOD)%MOD;
	ans=(ans-calc(0,-1)+MOD)%MOD;
	printf("%d",ans);
}
