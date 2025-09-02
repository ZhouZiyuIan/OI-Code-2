
#include<bits/stdc++.h>
using namespace std;
#define int long long
typedef long long ll;

ll read()
{
	ll x=0;char ch = getchar();
	while(!isdigit(ch)) ch =getchar();
	for(;isdigit(ch);ch=getchar()) x= (x<<3) + (x<<1) + (ch^48);
	return x;
}

const int N = 200005;
int n,m;
int dfn[N],id[N],dfnt,dep[N];
int top[N],siz[N],son[N],fa[N];
vector<int>gra[N];
struct edge
{
	int u,v,w;
}e[N];

void dfs1(int x,int f)
{
	siz[x] = 1;
	dep[x] = dep[f] + 1;
	fa[x] = f;
	for(auto v:gra[x])
	{
		if(v==f) continue;
		dfs1(v,x);
		siz[x]+=siz[v];
		if(siz[son[x]] < siz[v]) son[x] = v;
	}
}
void dfs2(int x,int topf)
{
	top[x] = topf;
	id[x] = ++dfnt;
	dfn[dfnt] = x;
	if(son[x]) dfs2(son[x],topf);
	for(auto v:gra[x])
	{
		if(v==fa[x] || v==son[x]) continue;
		dfs2(v,v);
	}
}

int t[N<<2];
void build(){
	memset(t,0x3f,sizeof t);
}
#define ls (p<<1)
#define rs (p<<1|1)
void getmin(int x,int y,int k,int p=1,int l=1,int r=n)
{
	if(x<=l && r<=y){
		t[p] = min(k,t[p]);
		return ;
	}
	int mid = l + r >> 1;
	if(x<=mid) getmin(x,y,k,ls,l,mid);
	if(y>mid) getmin(x,y,k,rs,mid+1,r);
}

int query(int x,int p=1,int l=1,int r=n)
{
	if(l==r) return t[p];
	int mid = l + r >> 1;
	if(x<=mid) return min(t[p],query(x,ls,l,mid));
	else return min(t[p],query(x,rs,mid+1,r));
}
int LCA(int x,int y)
{
	while(top[x]!=top[y])
	{
		if(dep[top[x]] < dep[top[y]]) swap(x,y);
		x = fa[top[x]];
	}
	if(dep[x] < dep[y]) swap(x,y);
	return y;
}
void solve(int x,int y,int k)
{
	
	int lca = LCA(x,y);
	while(top[x]!=top[lca])
	{
		getmin(id[top[x]],id[x],k);
		x = fa[top[x]];
	}
	if(x!=lca) getmin(id[lca]+1,id[x],k);
	
	while(top[y]!=top[lca])
	{
		getmin(id[top[y]],id[y],k);
		y = fa[top[y]];
	}
	
	if(y!=lca) getmin(id[lca]+1,id[y],k);
}
#define pa pair<int,int>
#define se second
#define fi first
#define ma(x,y) make_pair(x,y)
map<pa,int>mp;

signed main()
{
	n = read();m=read();
	for(int i=1;i<=m;i++){
		e[i].u = read();
		e[i].v = read();
		e[i].w = read();
	}
	for(int i=1;i<n;i++)
	{
		int u = read();
		int v = read();
		gra[u].emplace_back(v);
		gra[v].emplace_back(u);
		mp[ma(u,v)] = mp[ma(v,u)] = 1;
	}
	dfs1(1,0);
	dfs2(1,1);
	build();
	for(int i=1;i<=m;i++)
	{
		if(mp.count(ma(e[i].u,e[i].v))) continue;
		solve(e[i].u,e[i].v,e[i].w);
	}
	long long ans = 0;
	for(int i=1;i<=m;i++)
	{
		if(mp.count(ma(e[i].u,e[i].v)))
		{
			if(dep[e[i].u] > dep[e[i].v]) swap(e[i].u,e[i].v);
			ans += max(0ll,e[i].w-query(id[e[i].v]));
		}
	}
	cout << ans;
	
	return 0;
}