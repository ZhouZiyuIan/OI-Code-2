#pragma GCC optimize(2,3,"Ofast")
#include<stdio.h>
#include<ctype.h>
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
int n,d,a[100001],cnt[100001][2],cnt1,max;
int main(){
#ifndef _WIN64
	freopen("seq.in","r",stdin);
	freopen("seq.out","w",stdout);
#endif
	read(&n);
	read(&d);
	for(int i=0;i<n;++i){
		read(&a[i]);
		cnt1+=a[i];
	}
	for(int i=0;i<n;++i)cnt[i%d][a[i]]++;
	for(int i=0;i<d;++i)max<cnt[i][1]?max=cnt[i][1]:0;
	write(cnt1-max);
}
