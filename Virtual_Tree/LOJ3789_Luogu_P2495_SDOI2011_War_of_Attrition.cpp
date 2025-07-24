#pragma GCC optimize(3,"Ofast")
#include<stdio.h>
#include<stdlib.h>
#include<unordered_set>
using namespace std;
typedef struct{
	struct edg{
		int v,w,nxt;
	}e[1000001];
	int head[500001],cnt;
	void add(int u,int v,int w){
		e[++cnt].v=v;
		e[cnt].w=w;
		e[cnt].nxt=head[u];
		head[u]=cnt;
	}
}graph;
graph t1,t2;
int n,u,v,w,fa[500001][21],mind[500001][21],dfn[500001],cnt,dep[500001],dis[500001],m,k,a[500001],sta[500001],top,d,lca;
long long f[500001];
unordered_set<int>s;
void dfs1(int u,int f){
	dfn[u]=++cnt;
	dep[u]=dep[f]+1;
	fa[u][0]=f;
	for(int i=1;i<=20;++i){
		fa[u][i]=fa[fa[u][i-1]][i-1];
		mind[u][i]=min(mind[u][i-1],mind[fa[u][i-1]][i-1]);
	}
	for(int i=t1.head[u];i;i=t1.e[i].nxt){
		int v=t1.e[i].v,w=t1.e[i].w;
		if(v!=f){
			dis[v]=dis[u]+w;
			mind[v][0]=w;
			dfs1(v,u);
		}
	}
}
int cmp(const void *a,const void *b){return (dfn[*(int*)a]-dfn[*(int*)b]);}
int getlca(int x,int y){
	d=1<<30;
	if(dep[x]>dep[y]){
		int tmp=x;
		x=y;
		y=tmp;
	}
	for(int i=20;i>=0;i--){
		if(dep[y]-(1<<i)>=dep[x]){
			d=min(d,mind[y][i]);
			y=fa[y][i];
		}
	}
	if(x==y)return x;
	for(int i=20;i>=0;i--){
		if(fa[x][i]!=fa[y][i]){
			d=min(d,min(mind[x][i],mind[y][i]));
			x=fa[x][i],y=fa[y][i];
		}
	}
	return fa[x][0];
}
void dfs2(int u){
	f[u]=0;
	for(int i=t2.head[u];i;i=t2.e[i].nxt){
		int v=t2.e[i].v,w=t2.e[i].w;
		dfs2(v);
		if(s.count(v))f[u]+=w;
		else f[u]+=min(f[v],1ll*w);
	}
	return;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<n;++i){
		scanf("%d%d%d",&u,&v,&w);
		t1.add(u,v,w);
		t1.add(v,u,w);
	}
	dfs1(1,1);
	scanf("%d",&m);
	while(m--){
		s.clear();
		scanf("%d",&k);
		for(int i=1;i<=k;++i){
			scanf("%d",&a[i]);
			s.insert(a[i]);
		}
		qsort(a,k+1,sizeof(int),cmp);
		top=sta[1]=1;
		t2.head[1]=0;
		for(int i=1;i<=k;++i){
			lca=getlca(a[i],sta[top]);
			if(lca!=sta[top]){
				while(dfn[lca]<dfn[sta[top-1]]){
					u=sta[top-1];
					v=sta[top];
					getlca(u,v);
					t2.add(u,v,d);
					--top;
				}
				if(dfn[lca]>dfn[sta[top-1]]){
					getlca(lca,sta[top]);
					t2.head[lca]=0;
					t2.add(lca,sta[top],d);
					sta[top]=lca;
				}
				else{
					u=sta[top-1];
					v=sta[top];
					getlca(u,v);
					t2.add(u,v,d);
					--top;
				}
			}
			t2.head[a[i]]=0;
			sta[++top]=a[i];
		}
		while(top>1){
			u=sta[top-1];
			v=sta[top];
			getlca(u,v);
			t2.add(u,v,d);
			--top;
		}
		dfs2(1);
		printf("%lld\n",f[1]);
	}
}
