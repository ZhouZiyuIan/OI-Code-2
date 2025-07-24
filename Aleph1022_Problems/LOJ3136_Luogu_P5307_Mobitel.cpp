#include<stdio.h>
const int MOD=1e9+7;
int ceildiv(int a,int b){return a%b?(a/b)+1:(a/b);}
int r,s,n,grd[301][301],dival[1000001],nxt=1,blk[1000001],rev[1000001],f[2][301][2001];
int main(){
    scanf("%d%d%d",&r,&s,&n);
    for(int i=1;i<=r;++i)for(int j=1;j<=s;++j)scanf("%d",&grd[i][j]);
    for(int i=1;i<=n;++i){
        dival[i]=ceildiv(n,i);
        if(dival[i]!=dival[i-1]){
            blk[nxt++]=dival[i];
            rev[dival[i]]=nxt-1;
        }
    }
    f[1][1][rev[ceildiv(n,grd[1][1])]]=1;
    for(int i=1;i<=r;++i)for(int j=1;j<=s;++j)for(int k=1;k<nxt;++k){
        if(i!=r){
            f[(i&1)^1][j][rev[ceildiv(blk[k],grd[i+1][j])]]+=f[i&1][j][k];
            f[(i&1)^1][j][rev[ceildiv(blk[k],grd[i+1][j])]]%=MOD;
        }
        if(j!=s){
            f[i&1][j+1][rev[ceildiv(blk[k],grd[i][j+1])]]+=f[i&1][j][k];
            f[i&1][j+1][rev[ceildiv(blk[k],grd[i][j+1])]]%=MOD;
        }
        if(i!=r||j!=s||k!=nxt-1)f[i&1][j][k]=0;
    }
    printf("%d",f[r&1][s][nxt-1]);
}