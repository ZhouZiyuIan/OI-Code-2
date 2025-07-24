#include<stdio.h>
#include<queue>
using namespace std;
int pre[201],n,m,s,t,u,v,w,head[201],tot=1,vis[201],flag[201][201];
long long dis[2001],ans;
struct edg{
    int to,nxt;
    long long w;
}e[2001];
void add(int u,int v,int w){
    e[++tot].to=v;
    e[tot].nxt=head[u];
    e[tot].w=w;
    head[u]=tot;
}
int bfs(){
    queue<int>q;
    for(int i=1;i<=n;++i)vis[i]=0;
    dis[s]=9223372036854775807ll;
    vis[s]=1;
    q.push(s);
    while(!q.empty()){
        int x=q.front();
        q.pop();
        for(int i=head[x];i;i=e[i].nxt){
            int y=e[i].to;
            if(!vis[y]&&e[i].w){
                vis[y]=1;
                pre[y]=i;
                dis[y]=dis[x]<e[i].w?dis[x]:e[i].w;
                q.push(y);
                if(y==t)return 1;
            }
        }
    }
    return 0;
}
void upd(){
    int x=t;
    while(x!=s){
        int i=pre[x];
        e[i].w-=dis[t];
        e[i^1].w+=dis[t];
        x=e[i^1].to;
    }
    ans+=dis[t];
}
int main(void){
    scanf("%d%d",&m,&n);
    s=1;
    t=n;
    for(int i=0;i<m;++i){
        scanf("%d%d%d",&u,&v,&w);
        if(flag[u][v]==0){
            add(u,v,w);
            add(v,u,0);
            flag[u][v]=tot;
        }
        else{
            e[flag[u][v]-1].w+=w;
        }
    }
    while(bfs())upd();
    printf("%lld",ans);
    return 0;
}
