#include<stdio.h>
#include<stdlib.h>
int T,n,a[200001],f1,f2;
int abs(int x){return x<0?-x:x;}
int cmp(const void*a,const void*b){return (abs(*(int*)a)-abs(*(int*)b));}
main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		for(int i=0;i<n;++i)scanf("%d",&a[i]);
		qsort(a,n,sizeof(int),cmp);
		f2=f1=1;
		for(int i=1;i<n-1;++i)if((long long)a[i]*(long long)a[i]!=(long long)a[i-1]*(long long)a[i+1])f2=0;
		for(int i=0;i<n-1;++i)if(abs(a[i])!=abs(a[i+1]))f1=0;
		if(f1){
			int cnt=0;
			for(int i=0;i<n;++i){
				if(a[i]>0)cnt++;
				else cnt--;
			}
			if(abs(cnt)<=1)f2=1;
		}
		puts(f2?"Yes":"No");
	}
}
