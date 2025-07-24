#include<cstdio>
#include<queue>
#include<cstring>
using namespace std;
typedef long long ll;
ll S,T,dis[100001],head[100001],now[100001],cnt = -1,n,m,u,v,w,ans;
struct edg{
	ll to,nxt,cap;
}e[100001];
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
	now[S] = head[S];
	q.emplace(S);
	while(!q.empty())
	{
		ll u=q.front();
		q.pop();
		for(ll i = head[u];i != -1;i = e[i].nxt)
		{
			ll v = e[i].to;
			if(e[i].cap > 0 && dis[v] == -1)
			{
				dis[v] = dis[u] + 1;
				q.emplace(v);
				now[v] = head[v];
				if(v == T)
				{
					return 1;
				}
			}
		}
	}
	return 0;
}
ll dfs(ll u,ll f)
{
	if(u == T || !f)
	{
		return f;
	}
	ll flow = f;
	for(ll i = now[u];i != -1;i = e[i].nxt)
	{
		now[u] = i;
		ll v = e[i].to;
		if(flow && e[i].cap > 0 && (dis[v] == dis[u] + 1))
		{
			ll f = dfs(v,min(flow,e[i].cap));
			if(f == 0)
			{
				dis[v] = -1;
			}
			flow -= f;
			e[i].cap -= f;
			e[i ^ 1].cap += f;
		}
	}
	return f - flow;
}
ll dinic()
{
	ll maxFlow = 0;
	while(bfs())
	{
		maxFlow += dfs(S,0x3f3f3f3f);
	}
	return maxFlow;
}
int main()
{
	memset(head,-1,sizeof(head));
	scanf("%lld%lld",&n,&m);
	S = 0;
	T = n + 1;
	for(int i = 1;i <= n; i++)
	{
		scanf("%lld%lld",&u,&v);
		add(S,i,u);
		add(i,S,0);
		add(i,T,v);
		add(T,i,0);
	}
	for(int i = 1;i <= m; i++)
	{
		scanf("%lld%lld%lld",&u,&v,&w);
		add(u,v,w);
		add(v,u,0);
		add(v,u,w);
		add(u,v,0);
	}
	printf("%lld",dinic());
}
