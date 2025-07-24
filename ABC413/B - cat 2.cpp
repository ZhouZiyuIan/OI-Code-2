#include<iostream>
#include<unordered_map>
using namespace std;
unordered_map<string,bool>cz;
int n,cnt;
string s[101];
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	for(int i=0;i<n;++i)cin>>s[i];
	for(int i=0;i<n;++i)for(int j=0;j<n;++j)if(!cz.count(s[i]+s[j])&&i!=j){
		cz[s[i]+s[j]]=1;
		cnt++;
	}
	cout<<cnt;
}
