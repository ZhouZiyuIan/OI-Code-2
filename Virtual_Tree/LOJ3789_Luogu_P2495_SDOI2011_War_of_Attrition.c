#include<stdio.h>
typedef struct{
	struct edg{
		int v,w,nxt;
	}e[1000001];
	int head[500005],cnt;
	void addedge(int u,int v,int w){
		e[++cnt].v=v;
		e[cnt].w=w;
		e[cnt].nxt=head[u];
		head[u]=cnt;
	}
}graph;
graph t1,t2;
int n,u,v,w;
int main(){
	scanf("%d",&n);
	for(int i=1;i<n;++i){
		scanf("%d%d%d",&u,&v,&w);
		t1.addedge(u,v,w);
		t1.addedge(v,u,w);
	}
}
