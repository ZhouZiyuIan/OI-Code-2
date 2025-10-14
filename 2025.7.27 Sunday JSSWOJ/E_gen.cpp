#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int main(){
	srand(time(0));
	freopen("data.in","w",stdout);
	printf("300000 1\n");
	for(int i=0;i<300000;++i){
		printf("%d ",(rand()*100+rand()) % 1000000);
	}
}
