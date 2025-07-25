#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=205;
int head[N*N*2],to[N*N*8],nxt[N*N*8],cnt=1,n,ans,tot=0;
int vis[N*N*2],cp[N*N*2];
int fx[9]={0,-1,-2,1,2,-1,-2,1,2};
int fy[9]={0,-2,-1,-2,-1,2,1,2,1};//���Ʒ������顣 
char s[N][N];
void add(int u,int v){
	to[cnt]=v;
	nxt[cnt]=head[u];
	head[u]=cnt++;
} 
bool dfs(int x){
	for(int i=head[x];i;i=nxt[i]){
		int v=to[i];
		if(vis[v]) continue;
		vis[v]=true;
		if(!cp[v]||dfs(cp[v])){
		    cp[v]=x;
	    	return true;
		}
	}
	return false;
}//�������㷨���� 
int main(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>s[i]+1;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(s[i][j]=='1'){
			    tot++;
			    continue;
			}//��¼���ܷ���ĵ�ĸ����� 
			for(int k=1;k<=8;k++){
				int x=i+fx[k],y=j+fy[k];
				if(s[x][y]=='1') continue; 
				if(x>=1&&x<=n&&y>=1&&y<=n&&(i+j)%2==0) add((i-1)*n+j,(x-1)*n+y+n*n);
				//�ڿ����໥�����ĵ�֮�����ߡ� 
			} 
		}
	}
	for(int i=1;i<=n*n;i++){
		memset(vis,0,sizeof(vis));
		int k=dfs(i);
		ans+=k;//ͳ�����ƥ������ 
	}
	printf("%d\n",n*n-tot-ans);//����������㼯=�ܵ���-���ƥ������ 
	return 0;
}
