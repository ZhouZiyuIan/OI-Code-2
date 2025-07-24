#include<stdio.h>
int n,m,a,tot;
main(){
	scanf("%d%d",&n,&m);
	while(n--){
		scanf("%d",&a);
		tot+=a;
	}
	puts(tot<=m?"Yes":"No");
}
