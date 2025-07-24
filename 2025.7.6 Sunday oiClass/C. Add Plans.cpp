#include<stdio.h>
#include<ctype.h>
#ifdef _WIN64
#define getchar_unlocked() _getchar_nolock()
#define putchar_unlocked(_c) _putchar_nolock(_c)
#endif
#define ll long long
const int MOD=998244353;
ll qpow(ll a,ll b){
	a%=MOD;
	long long res=1;
	while(b>0){
		if(b&1)res=res*a%MOD;
		a=a*a%MOD;
		b>>=1;
	}
	return res;
}
char s;
int n[100001],lenn;
ll ans,sum;
int main(){
#ifndef _WIN64
	freopen("add.in","r",stdin);
	freopen("add.out","w",stdout);
#endif
	s=getchar_unlocked();
	while(isdigit(s)){
		n[lenn++]=(s^48);
		s=getchar_unlocked();
	}
	for(int i=0;i<lenn;++i){
		ans=((ans+(ans<<1)+(ans<<3))%MOD+qpow(2,i)*n[i])%MOD;
		sum=(((sum<<1)+(sum<<3))+n[i])%MOD;
	}
	printf("%lld\n",((ans<<1)-sum+MOD)%MOD);
}
