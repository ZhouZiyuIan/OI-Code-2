#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <functional>
using namespace std;
int n, k, x;
vector<string>all;
string cur;
signed main(){
	cin >> n >> k >> x;
	vector<string>s(n);
	for(signed i=0;i<n;++i)cin >> s[i];
	sort(s.begin(),s.end());
	all.reserve(pow(n,k));
	function<void(int)>dfs=[&](signed dep){
		if(dep==k){
			all.emplace_back(cur);
			return;
		}
		for(signed i=0;i<n;++i){
			cur+=s[i];
			dfs(dep+1);
			cur.resize(cur.size()-s[i].size());
		}
	};
	dfs(0);
	sort(all.begin(),all.end());
	cout << all[x-1];
}
