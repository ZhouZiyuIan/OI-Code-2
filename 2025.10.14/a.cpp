//
// Created by 118 on 25-10-14.
//
#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int mod=998244353;
int t;
string a;
signed main(){
//	freopen("a.in","r",stdin);
//	freopen("a.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>t;
	while(t--){
		cin>>a;
		int sum=0,f=1;
		ll ans=1;
		for(int i=0;i<a.size()-1;i++){
			sum+=f;if(sum>=mod)sum-=mod;
			if(a[i]=='1')f^=sum^=f^=sum;
			ans+=f;
		}
		cout<<ans%mod<<'\n';
	}
	return 0;
}
