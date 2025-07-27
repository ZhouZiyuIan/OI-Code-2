#include<stdio.h>
int n,l,r;
char s[101];
int main(){
	scanf("%d%d%d%s",&n,&l,&r,s);
	for(int i=l-1;i<r;++i){
		if(s[i]=='x'){
			puts("No");
			return 0;
		}
	}
	puts("Yes");
}
