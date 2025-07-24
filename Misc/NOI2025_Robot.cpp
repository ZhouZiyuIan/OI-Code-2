#include<stdio.h>
int c,n,m,k,d,v,len,tot,head[300001];
long long v[250001],w[250002];
struct edg{
    int nxt,val,to;
}e[250001];
void add(int u,int v,int w){
    e[++tot].to=v;
    e[tot].val=w;
    e[tot].nxt=head[u];
    head[u]=tot;
}
int main(){
    scanf("%d%d%d%d",&c,&n,&m,&k);
    for(int i=1;i<k;++i)scanf("%lld",&v[i]);
    for(int i=2;i<=k;++i)scanf("%lld",&w[i]);
    for(int i=1;i<=n;++i){
        scanf("%d",&d);
        
    }
}