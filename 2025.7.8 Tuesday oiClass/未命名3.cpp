#include<conio.h>
#include<time.h>
#include<stdlib.h>
#include<stdio.h>
int a,rd;//a 为按键输入值的变量，rd 是随机数 
int l=0,r=50;//l 和 r 是指随机数从l~r中选取（l 和 r 需要是非负整数且 <RAND_MAX）
int seed=0;//seed 为随机数的种子（为 0 则以当前使用 time(0) 得出的时间作为种子）
int main(){
	srand(seed?seed:time(0));//初始化随机数种子（伪随机数）
	if(l>r)a=l,l=r,r=a;//避免l>r的情况导致程序输出错误结果
	while(1){
		rd=rand()%(r-l+1)+l;//生成随机数 
		printf("%d",rd);//输出当前随机数
		if(_kbhit()){//如果任一按键按下则触发判断
			a=_getch();//以不回显的形式读入一个字符 
			if(a==' '){//如果是空格 
				printf("\n请按空格键继续. . .");//输出提示 
				a=_getch();//按一次空格键暂停看随机数，再按一次空格键就继续随机
			}
			else if(a==27)exit(0);//如果按了 Esc 键就退出程序
			else continue;//如果不是空格键或 Esc 键就继续生成随机数 
			while(a!=' '){
				if(a==27){//如果按了 Esc 键就退出程序
					system("cls");//清屏
					printf("%d",rd);//输出当前随机数 
					exit(0);//退出程序 
				}
				a=_getch();//如果按下的按键不是空格键，则继续读入，直到按下空格键 
			}
		}
		system("cls");//不按按键时清屏并刷新新随机数 
	}
}
