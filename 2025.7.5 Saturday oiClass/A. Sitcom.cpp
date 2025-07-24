#pragma GCC optimize(2,3,"Ofast")
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<stack>
using namespace std;
#ifdef _WIN64
#define getchar_unlocked() _getchar_nolock()
#define putchar_unlocked(_c) _putchar_nolock(_c)
#endif
#include<ctype.h>
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
void write(__int128 x){
	if(x<0)x=-x,putchar_unlocked(45);
	if(x>9)write(x/10);
	putchar_unlocked(x%10+48);
}
int n,tlmin,trmin,lmin[2000001],rmin[2000001],lmax[2000001],rmax[2000001],tlmax,trmax;
__int128 ans,mnans,mxans,minmax,maxmin;
__int128 h[2000001],tremn[4000001],tremx[4000001];
stack<int>smin,smax;
void build(__int128 k,__int128 l,__int128 r){
	if(l==r){
		tremx[k]=tremn[k]=h[l];
		return;
	}
	__int128 mid=(l+r)>>1;
	build(k<<1,l,mid);
	build(k<<1|1,mid+1,r);
	tremx[k]=max(tremx[k<<1],tremx[k<<1|1]);
	tremn[k]=min(tremn[k<<1],tremn[k<<1|1]);
}
__int128 qmx(__int128 goall,__int128 goalr,__int128 lcur,__int128 rcur,__int128 cur){
	if(goall<=lcur&&goalr>=rcur)return tremx[cur];
	__int128 mid=(lcur+rcur)>>1,ret=0;
	if(goall<=mid)ret=max(qmx(goall,goalr,lcur,mid,cur<<1),ret);
	if(goalr>mid)ret=max(qmx(goall,goalr,mid+1,rcur,cur<<1|1),ret);
	return ret;
}
__int128 qmn(__int128 goall,__int128 goalr,__int128 lcur,__int128 rcur,__int128 cur){
	if(goall<=lcur&&goalr>=rcur)return tremn[cur];
	__int128 mid=(lcur+rcur)>>1,ret=0;
	if(goall<=mid)ret=min(qmn(goall,goalr,lcur,mid,cur<<1),ret);
	if(goalr>mid)ret=min(qmn(goall,goalr,mid+1,rcur,cur<<1|1),ret);
	return ret;
}
int main(){
#ifndef _WIN64
	freopen("sitcom.in","r",stdin);
	freopen("sitcom.out","w",stdout);
#endif
	read(&n);
	for(int i=1;i<=n;++i){
		read(&h[i]);
		lmax[i]=lmin[i]=0;
		rmax[i]=rmin[i]=n+1;
	}
	build(1,1,n);
	for(int i=1;i<=n;++i){
		while(!smin.empty()&&h[smin.top()]>h[i]){
			rmin[smin.top()]=i;
			smin.pop();
		}
		if(!smin.empty())lmin[i]=smin.top();
		smin.emplace(i);
	}
	for(int i=1;i<=n;++i){
		while(!smax.empty()&&h[smax.top()]<=h[i]){
			rmax[smax.top()]=i;
			smax.pop();
		}
		if(!smax.empty())lmax[i]=smax.top();
		smax.emplace(i);
	}
	for(int i=1;i<=n;++i){
		tlmin=lmin[i]+1;
		trmin=rmin[i]-1;
		mnans=h[i]*(trmin-tlmin+1);
		minmax=qmx(tlmin,trmin,1,n,1);
		mnans*=minmax;
		mnans>ans?ans=mnans:0;
		tlmax=lmax[i]+1;
		trmax=rmax[i]-1;
		mxans=h[i]*(trmax-tlmax+1);
		maxmin=qmn(tlmax,trmax,1,n,1);
		mxans*=maxmin;
		mxans>ans?ans=mxans:0;
	}
	write(ans);
}
