#pragma GCC optimize(2,3,"Ofast")
#include<stdio.h>
#include<ctype.h>
#include<vector>
using namespace std;
#ifdef _WIN64
#define getchar_unlocked() _getchar_nolock()
#define putchar_unlocked(_c) _putchar_nolock(_c)
#endif
template<typename T>
void read(T*w){
	T f=1,x=0;
	char s=getchar_unlocked();
	while(!isdigit(s)){
		if(s=='-')f=-f;
		s=getchar_unlocked();
	}
	do{
		x=(x<<1)+(x<<3)+(s^48);
		s=getchar_unlocked();
	}while(isdigit(s));
	x*=f;
	*w=x;
}
template<typename T>
void write(T x){
	if(x<0)x=-x,putchar_unlocked(45);
	if(x>9)write(x/10);
	putchar_unlocked(x%10+48);
}
int n,m,q,p,b,ans;
bool res[1000001],chg[1000001];
int main(){
	read(&n);
	read(&m);
	read(&q);
	for(int i=1;i<=n;++i){
		read(&p);
		res[i]=p&1;
	}
	vector<vector<vector<int>>>f(n+1,vector<vector<int>>(n+1,vector<int>(2,0)));
	while(m--){
		read(&p);
		read(&b);
		res[p]=b&1;
		chg[p]=1;
	}
	while(q--){
		read(&b);
		read(&p);
		if(b&1)chg[p]=0;
		else{
			read(&m);
			chg[p]=1;
			res[p]=m&1;
		}
		for(int i=1;i<=n;++i){
			for(int j=1;j<=n;++j){
				if(chg[i]){
					if(res[i]){
						if(chg[i-1])f[i][j][0]=f[i][j][1]=f[i-1][j-1][res[i-1]]+(res[i-1]==res[i]);
						else f[i][j][0]=f[i][j][1]=min(f[i-1][j-1][0]+1,f[i-1][j-1][1]);
					}
					else{
						if(chg[i-1])f[i][j][0]=f[i][j][1]=f[i-1][j-1][res[i-1]]+(res[i-1]==res[i]);
						else f[i][j][0]=f[i][j][1]=min(f[i-1][j][0],f[i-1][j][1]+1);
					}
					
				}
				else{
					f[i][j][0]=min(f[i-1][j][0],f[i-1][j][1]+1);
					f[i][j][1]=min(f[i-1][j-1][0]+1,f[i-1][j-1][1]);
				}
			}
		}
		for(int i=1;i<=n;++i)ans=min(ans,min(f[n][i][0],f[n][i][1]));
		printf("%d\n",f[2][1][0]);
	}
}
