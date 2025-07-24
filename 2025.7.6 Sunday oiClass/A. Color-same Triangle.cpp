#pragma GCC optimize(3,"Ofast")
#include<stdio.h>
#include<ctype.h>
#ifdef _WIN64
#define getchar_unlocked() _getchar_nolock()
#define putchar_unlocked(_c) _putchar_nolock(_c)
#endif
void readInt(int*w){
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
void readULL(unsigned long long*w){
	unsigned long long f=1,x=0;
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
void write(unsigned long long x){
	if(x<0)x=-x,putchar_unlocked(45);
	if(x>9)write(x/10);
	putchar_unlocked(x%10+48);
}
int n;
unsigned long long zj=1,C=1,sum,a,b;
int main(){
	#ifndef _WIN64
	freopen("tri.in","r",stdin);
	freopen("tri.out","w",stdout);
	#endif
	readInt(&n);
	for(int i=0;i<n;++i){
		readULL(&a);
		readULL(&b);
		sum+=a*b;
	}
	for(int i=2;i<n-1;++i){
		zj+=i;
		C+=zj;
	}
	write(C-(sum>>1));
}
