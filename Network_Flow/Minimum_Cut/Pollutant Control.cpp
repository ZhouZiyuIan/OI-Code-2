#include<cstdio>
#include<queue>
using namespace std;
typedef long long ll;
const ll MOD = 2025;
ll S,T,dis[10001],head[10001],now[10001],cnt = 1,n,m,u,v,w,ans;
struct edg{
	ll to,nxt,cap;
}e[10001];
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
	for(ll i = 1;i <= n;i++)
	{
		dis[i] = 9223372036854775807ll;
	}
	dis[S] = 0;
	now[S] = head[S];
	q.emplace(S);
	while(!q.empty())
	{
		ll u=q.front();
		q.pop();
		for(ll i = head[u];i;i = e[i].nxt)
		{
			ll v = e[i].to;
			if(e[i].cap > 0 && dis[v] == 9223372036854775807ll)
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
ll dfs(ll u,ll flow)
{
	if(u == T)
	{
		return flow;
	}
	ll ret = 0, f;
	for(ll i = now[u];i && flow;i = e[i].nxt)
	{
		now[u] = i;
		ll v = e[i].to;
		if(e[i].cap > 0 && (dis[v] == dis[u] + 1))
		{
			f = dfs(v,min(flow,e[i].cap));
			if(f == 0)
			{
				dis[v] = 9223372036854775807ll;
			}
			ret += f;
			flow -= f;
			e[i].cap -= f;
			e[i ^ 1].cap += f;
		}
	}
	return ret;
}
ll dinic()
{
	ll maxFlow = 0;
	while(bfs())
	{
		maxFlow += dfs(S,9223372036854775807ll);
	}
	return maxFlow;
}
int main()
{
	scanf("%lld%lld",&n,&m);
	S = 1;
	T = n;
	while(m--)
	{
		scanf("%lld%lld%lld",&u,&v,&w);
		add(u,v,w * MOD + 1);
		add(v,u,0);
	}
	ans = dinic();
	printf("%lld %lld",ans / MOD,ans % MOD);
}
