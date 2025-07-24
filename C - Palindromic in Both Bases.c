#include<stdio.h>
int A;
long long N,ans;
long long r(long long a,long long b,int m){
	while(b){
		a=a*m+b%m;
		b/=m;
	}
	return a;
}
int main(){
    scanf("%d%lld",&A,&N);
    for(int i=1;i<=1e6;++i){
        long long tmp=r(i,i,10);
        if(tmp<=N&&tmp==r(0,tmp,A))ans+=tmp;
		tmp=r(i/10,i,10);
		if(tmp<=N&&tmp==r(0,tmp,A))ans+=tmp;
    }
    printf("%lld",ans);
}