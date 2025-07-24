#pragma GCC optimize(3,"Ofast")
#include<stdio.h>
long long ans;
int k,n;
int p[20001],f[20001];
char s[20001];
void get_p(int x){
	p[1]=0;
	int i=2,j=0;
	for(;i<=n-x;++i){
		while(j>0&&s[i+x]!=s[j+x+1])j=p[j];
		if(s[i+x]==s[j+x+1])++j;
		p[i]=j;
		if(f[j])f[i]=f[j];
		else if(j>=k)f[i]=j;
		else f[i]=0;
		if(f[i]&&(f[i]<<1)<i)++ans;
	}
}
int main(){
	scanf("%s%d",s+1,&k);
	for(;s[n+1];++n);
	int i=1;
	for(;i<=n;++i)get_p(i-1);
	printf("%lld",ans);
}
