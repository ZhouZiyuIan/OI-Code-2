#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
typedef int ll;
ll S,T,dis[200001],head[200001],cnt,n,m,x,y,w,a,b;
struct edg{
	ll to,nxt,cap;
}e[200001];
void add(ll u, ll v, ll w)
{
	e[++cnt].to = v;
	e[cnt].nxt = head[u];
	e[cnt].cap = w;
	head[u] = cnt;
}
ll bfs()
{
	queue<int>q;
	memset(dis,-1,sizeof(dis));
	dis[S] = 0;
	q.emplace(S);
	while(!q.empty())
	{
		ll u=q.front();
		q.pop();
		for(ll i = head[u];i;i = e[i].nxt)
		{
			ll v = e[i].to;
			if(e[i].cap && dis[v] == -1)
			{
				dis[v] = dis[u] + 1;
				q.emplace(v);
			}
		}
	}
	return dis[T] != -1;
}
ll dfs(ll u,ll lim)
{
	if(u == T || !lim)
	{
		return lim;
	}
	int w,flow = 0;
	for(int i = head[u];i;i = e[i].nxt)
	{
		int v = e[i].to;
		if(dis[v] == dis[u] + 1 && (w = dfs(v,min(lim,e[i].cap))))
		{
			flow += w;
			e[i].cap -= w;
			e[((i - 1) ^ 1) + 1].cap += w;
			lim -= w;
			if(!lim) break;
		}
	}
	return flow;
}
ll dinic()
{
	ll maxFlow = 0;
	while(bfs())
	{
		maxFlow += dfs(S,1e9);
	}
	return maxFlow;
}
int main()
{
	scanf("%d%d%d%d",&n,&m,&S,&T);
	for(int i = 1;i <= m; i++)
	{
		scanf("%d%d",&x,&y);
		a = x;
		b = y;
		if(x != S && x != T)
		{
			a += n;
		}
		if(y != S && y != T)
		{
			b += n;
		}
		add(a,y,1);
		add(y,a,0);
		add(b,x,1);
		add(x,b,0);
	}
	for(int i = 1 ; i <= n; i++)
	{
		if(i != S && i != T)
		{
			add(i,i + n,1);
			add(i + n,i,0);
		}
	}
	printf("%d",dinic());
}
