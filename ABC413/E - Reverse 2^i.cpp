#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int temp[1<<18],T,n,len;
int lex_compare(const int*a,const int*b,int len){
	for(int i=0;i<len;++i){
		if(a[i]<b[i])return -1;
		if(a[i]>b[i])return 1;
	}
	return 0;
}
void copy(int*dest,const int*src,int len){for(int i=0;i<len;++i)dest[i]=src[i];}
void solve(int*P,int len){
	if(len==1)return;
	int mid=len>>1;
	solve(P,mid);
	solve(P+mid,mid);
	for(int i=0;i<mid;++i)temp[i]=P[mid+i];
	for(int i=0;i<mid;++i)temp[mid+i]=P[i];
	if(lex_compare(temp,P,len)<0)copy(P, temp, len);
}
main(){
	scanf("%d",&T);
	int *P=(int*)malloc(300000*sizeof(int));
	while(T--){
		scanf("%d", &n);
		len=1<<n;
		for(int i=0;i<len;++i)scanf("%d",&P[i]);
		solve(P,len);
		for(int i=0;i<len;++i)printf("%d ",P[i]);
		putchar(10);
	}
	free(P);
}

