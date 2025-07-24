#pragma GCC optimize(3,"Ofast")
#include<stdio.h>
#include<unordered_map>
#include<ctype.h>
using namespace std;
unordered_map<int,int>var;
#ifdef _WIN64
#define getchar_unlocked() _getchar_nolock()
#define putchar_unlocked(_c) _putchar_nolock(_c)
#endif
void read(int*w){
	int f=1,x=0;
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
void write(int x){
	if(x<0){
		x=-x;
		putchar_unlocked(45);
	}
	if(x>9)write(x/10);
	putchar_unlocked(x%10+48);
}
const int MOD=998244353,base=131;
int n,k,a[20001],fac[20001],hsh[20001],l,r,mid,ans;
void gen_hash(){
	fac[0]=1;
	for(int i=1;i<=n;++i)fac[i]=1ll*fac[i-1]*base%MOD;
	for(int i=1;i<=n;++i)hsh[i]=(hsh[i-1]+1ll*a[i]*fac[n-i]%MOD)%MOD;
}
int get_hash(int l,int r){return 1ll*(hsh[r]-hsh[l-1]+MOD)*fac[l]%MOD;}
bool chk(int x){
	var.clear();
	int mx=0,curh;
	for(int i=1;i+x-1<=n;++i){
		curh=get_hash(i,i+x-1);
		++var[curh];
		mx=max(mx,var[curh]);
	}
	return mx>=k;
}
int main(){
	read(&n);read(&k);
	for(int i=1;i<=n;++i)read(&a[i]);
	gen_hash();
	l=1;
	r=n;
	while(l<=r){
		mid=(l+r)>>1;
		if(chk(mid)){
			ans=mid;
			l=mid+1;
		}
		else{
			r=mid-1;
		}
	}
	write(ans);
}
