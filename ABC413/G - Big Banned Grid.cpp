#include<stdio.h>
#include<map>
#include<utility>
using namespace std;
map<pair<int,int>,int>vis,mp;
int h,w,k,r,c,dx[8]={0,0,-1,1,-1,1,-1,1},dy[8]={-1,1,0,0,-1,1,1,-1};
void dfs(int x,int y){
	if(vis[{x,y}])return;
	vis[{x,y}]=1;
	for(int i=0;i<8;++i)if(mp[{x+dx[i],y+dy[i]}])dfs(x+dx[i],y+dy[i]);
}
main(){
	scanf("%d%d%d",&h,&w,&k);
	for(int i=0;i<k;++i){
		scanf("%d%d",&r,&c);
		mp[{r,c}]=1;
	}
	for(int i=1;i<=w;++i)if(mp[{h,i}])dfs(h,i);
	for(int i=1;i<=h;++i)if(mp[{i,1}])dfs(i,1);
	for(int i=1;i<=w;++i)if(vis[{1,i}]){
		puts("No");
		return 0;
	}
	for(int i=1;i<=h;++i)if(vis[{i,w}]){
		puts("No");
		return 0;
	}
	puts("Yes");
}
