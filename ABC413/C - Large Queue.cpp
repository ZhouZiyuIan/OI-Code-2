#include<stdio.h>
long long sum,kelc[200001],ksig[200001],c,x,q,op,kcnt,khd=1;
int main(){
	scanf("%lld",&q);
	while(q--){
		scanf("%lld%lld",&op,&c);
		if(op==1){
			scanf("%lld",&x);
			kelc[++kcnt]=c;
			ksig[kcnt]=x;
		}
		else{
			sum=0;
			while(c>0){
				if(kelc[khd]<=c){
					sum+=kelc[khd]*ksig[khd];
					c-=kelc[khd++];
				}
				else{
					sum+=ksig[khd]*c;
					kelc[khd]-=c;
					c=0;
				}
			}
			printf("%lld\n",sum);
		}
	}
}
