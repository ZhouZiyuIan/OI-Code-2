#include<stdio.h>
int min,t,mins;
int main(){
	for(int d=1;d<=100;++d){
		min=2147483647;
		for(int t=1;t<=4000;++t){
			min>=((d/(t+1))+t)?(min=((d/(t+1))+t),mins=t):0;
//			printf("%d %d\n",min,mins);
		}
		printf("%d\n",mins);
	}
}
