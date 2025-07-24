#include<stdio.h>
typedef long long ll;
typedef __int128 I128;
#ifdef _WIN64
#define getchar_unlocked() _getchar_nolock()
#define putchar_unlocked(_c) _putchar_nolock(_c)
#endif
#define _U 0x01
#define _L 0x02
#define _D 0x04
#define _C 0x08
#define _P 0x10
#define _S 0x20
#define _X 0x40
#define _SP 0x80
extern unsigned char _ctype[];
#define isdigit(c) ((_ctype+1)[c]&(_D))
unsigned char _ctype[]={0x00,_C,_C,_C,_C,_C,_C,_C,_C,_C,_C|_S,_C|_S,_C|_S,_C|_S,_C|_S,_C,_C,_C,_C,_C,_C,_C,_C,_C,_C,_C,_C,_C,_C,_C,_C,_C,_C,_S|_SP,_P,_P,_P,_P,_P,_P,_P,_P,_P,_P,_P,_P,_P,_P,_P,_D,_D,_D,_D,_D,_D,_D,_D,_D,_D,_P,_P,_P,_P,_P,_P,_P,_U|_X,_U|_X,_U|_X,_U|_X,_U|_X,_U|_X,_U,_U,_U,_U,_U,_U,_U,_U,_U,_U,_U,_U,_U,_U,_U,_U,_U,_U,_U,_U,_P,_P,_P,_P,_P,_P,_L|_X,_L|_X,_L|_X,_L|_X,_L|_X,_L|_X,_L,_L,_L,_L,_L,_L,_L,_L,_L,_L,_L,_L,_L,_L,_L,_L,_L,_L,_L,_L,_P,_P,_P,_P,_C,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int readInt(int*w){
	int f=1,x=0;
	char s=getchar_unlocked();
	while(!isdigit(s)){
		if(s=='-')f=-f;
		else if(s==-1)return 0;
		s=getchar_unlocked();
	}
	do{
		x=(x<<1)+(x<<3)+(s^48);
		s=getchar_unlocked();
	}while(isdigit(s));
	x*=f;
	*w=x;
	return 1;
}
int readI128(I128*w){
	I128 f=1,x=0;
	char s=getchar_unlocked();
	while(!isdigit(s)){
		if(s=='-')f=-f;
		else if(s==-1)return 0;
		s=getchar_unlocked();
	}
	do{
		x=(x<<1)+(x<<3)+(s^48);
		s=getchar_unlocked();
	}while(isdigit(s));
	x*=f;
	*w=x;
	return 1;
}
void writeI128(I128 x){
	if(x<0){
		x=-x;
		putchar_unlocked(45);
	}
	if(x>9)writeI128(x/10);
	putchar_unlocked(x%10+48);
}
int n;
I128 m[100001],a[100001],M,A,gcd,x,y;
I128 exgcd(I128 a,I128 b,I128*x,I128*y){
	if(b==0){
		*x=1;
		*y=0;
		return a;
	}
	I128 d=exgcd(b,a%b,y,x);
	*y-=a/b**x;
	return d;
}
int main(){
	readInt(&n);
	for(int i=1;i<=n;++i){
		readI128(&m[i]);
		readI128(&a[i]);
	}
	M=m[1];
	A=a[1];
	for(int i=2;i<=n;++i){
		gcd=exgcd(M,m[i],&x,&y);
		if((A-a[i])%gcd){
			putchar_unlocked(45);
			putchar_unlocked(49);
			A=-998244353;
			break;
		}
		x=(A-a[i])/gcd*x%m[i];
		A-=x*M;
		M=M/gcd*m[i];
		A%=M;
	}
	if(A!=-998244353){
		A=(A+M)%M;
		writeI128(A);
	}
}
