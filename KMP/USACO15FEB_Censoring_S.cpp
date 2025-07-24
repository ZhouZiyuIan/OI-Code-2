#include<stdio.h>
char s[1000001],t[1000001];
int p[1000001],tlen,slen,f[1000001],st[1000001],top;
void init_p(char t[]){
	int j=0,i=2;
	for(;i<=tlen;++i){
		while(j&&t[j+1]!=t[i])j=p[j];
		if(t[j+1]==t[i])++j;
		p[i]=j;
	}
}
void kmp(char s[],char t[]){
	int j=0,i=1;
	for(;i<=slen;++i){
		while(j>0&&t[j+1]!=s[i])j=p[j];
		if(t[j+1]==s[i])++j;
		f[i]=j;
		st[++top]=i;
		if(j==tlen){
			top-=tlen;
			j=f[st[top]];
		}
	}
}
int main(){
	scanf("%s%s",s+1,t+1);
	for(;t[tlen+1];++tlen);
	for(;s[slen+1];++slen);
	init_p(t);
	kmp(s,t);
	for(int i=1;i<=top;++i)putchar(s[st[i]]);
} 
