#include<stdio.h>
#include<stdlib.h>
int n,m;
long long x[500001],b[500001],ans;
int cmp(const void*a,const void*b){return (*(long long*)a-*(long long*)b)>0?1:-1;}
int cmp1(const void*a,const void*b){return (*(long long*)b-*(long long*)a)>0?1:-1;}
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)scanf("%lld",&x[i]);
    qsort(x,n+1,sizeof(long long),cmp);
    for(int i=1;i<n;++i){
        b[i]=x[i+1]-x[i];
        ans+=b[i];
    } 
    b[0]=9223372036854775807ll;
    qsort(b,n,sizeof(long long),cmp1);
    for(int i=1;i<m;++i)ans-=b[i];
    printf("%lld",ans);
}