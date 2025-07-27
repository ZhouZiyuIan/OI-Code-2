#include<stdio.h>
#include<string.h>
char s[110],t[110];
int n,lsO;
int main(){
	scanf("%s",s);
	strcpy(t,s);
	n=strlen(s);
	for(int i=0;i<n;++i){
		if(s[i]=='.'){
			if(!lsO){
				t[i]='o';
				lsO=1;
			}
			else{
				t[i]='.';
			}
		}
		else{
			lsO=0;
		}
	}
	printf("%s",t);
}
