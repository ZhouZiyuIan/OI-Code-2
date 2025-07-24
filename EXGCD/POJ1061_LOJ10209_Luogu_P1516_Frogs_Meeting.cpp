#include<stdio.h>
long long x,y,m,n,l,r=0,A,B;
long long exgcd(long long a,long long b,long long &x,long long &y){
	if(b==0){
		x=1;
		y=0;
		return a;
	}
	r=exgcd(b,a%b,x,y);
	long long t=x;
	x=y;
	y=t-a/b*y;
	return r;
}
main(){
	scanf("%lld%lld%lld%lld%lld",&x,&y,&m,&n,&l);
	A=n-m;
    B=x-y;
	if(A<0){
		A=-A;
		B=-B;
	}
	exgcd(A,l,x,y);
	if(B%r)puts("Impossible");
	else printf("%lld",((x*(B/r))%(l/r)+(l/r))%(l/r));
}