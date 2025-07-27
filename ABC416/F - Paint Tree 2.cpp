#include<bits/stdc++.h>
using namespace std;
using ll=long long;
using i128=__int128_t;
struct DPVal{
	i128 val;
	int comps;
};
int N,K;
vector<ll>A;
vector<vector<int>>adj,children;
vector<int>parent,order;
vector<DPVal>dp0,dp1;
ll Tglobal;
void build_tree(int root=0){
	parent.assign(N,-1);
	children.assign(N,{});
	order.clear();
	order.reserve(N);
	vector<int>stk={root};
	parent[root]=-2;
	while(!stk.empty()){
		int u=stk.back();
		stk.pop_back();
		order.emplace_back(u);
		for(int v:adj[u]){
			if(parent[v]==-1){
				parent[v]=u;
				children[u].emplace_back(v);
				stk.emplace_back(v);
			}
		}
	}
	reverse(order.begin(),order.end());
}
void run_dp(){
	for(int u:order){
		i128 sum0=0;
		int comps0=0;
		vector<i128>deltas;
		deltas.reserve(children[u].size());
		for(int v:children[u]){
			DPVal& c0=dp0[v], c1=dp1[v];
			sum0+=c0.val;
			comps0+=c0.comps;
			deltas.emplace_back(c1.val-c0.val);
		}
		sort(deltas.begin(),deltas.end(),greater<i128>());
		i128 d0=0,d1=deltas.size()>0?deltas[0]:(i128)(-9e30),d2=deltas.size()>1?deltas[0]+deltas[1]:(i128)(-9e30),best0_val = sum0;
		int best0_comp = comps0;
		i128 v=sum0+(i128)A[u]-(i128)Tglobal;
		if(v>best0_val){
			best0_val=v;
			best0_comp=comps0+1;
		}
		if(deltas.size()>0){
			i128 v=sum0+d1+(i128)A[u]-(i128)Tglobal;
			if(v>best0_val){
				best0_val=v;
				best0_comp=comps0+1;
			}
		}
		if(deltas.size()>1){
			i128 v=sum0+d2+(i128)A[u]-(i128)Tglobal;
			if(v>best0_val){
				best0_val=v;
				best0_comp=comps0 + 1;
			}
		}
		dp0[u].val=best0_val;
		dp0[u].comps=best0_comp;
		i128 best1_val=sum0+(i128)A[u];
		int best1_comp=comps0;
		if(deltas.size()>0) {
			i128 v=sum0+d1+(i128)A[u];
			if(v>best1_val){
				best1_val=v;
				best1_comp=comps0;
			}
		}
		dp1[u].val=best1_val;
		dp1[u].comps=best1_comp;
	}
}
int main(){
	cin>>N>>K;
	A.resize(N);
	for(int i=0;i<N;++i){
		cin>>A[i];
	}
	adj.assign(N,{});
	for(int i=0;i<N-1;++i){
		int u,v;
		cin>>u>>v;
		--u;
		--v;
		adj[u].emplace_back(v);
		adj[v].emplace_back(u);
	}
	build_tree(0);
	dp0.resize(N);
	dp1.resize(N);
	ll low=0,high=1000000005LL;
	while(low<high){
		ll mid=(low+high)>>1;
		Tglobal=mid;
		run_dp();
		int comps=dp0[0].comps;
		if(comps>K)low=mid+1;
		else high=mid;
	}
	Tglobal=low;
	run_dp();
	i128 best_val=dp0[0].val+(i128)Tglobal*dp0[0].comps;
	long long ans=(long long)best_val;
	cout<<ans<<'\n';
}
