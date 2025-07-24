#pragma GCC optimize(3,"Ofast","inline","fast-math")
#include<stdio.h>
#include<ctype.h>
#ifdef _WIN64
#define getchar_unlocked() _getchar_nolock()
#define putchar_unlocked(_c) _putchar_nolock(_c)
#endif
#define ll long long
void read(long long*w){
	long long f=1,x=0;
	char s=getchar_unlocked();
	while(!isdigit(s)){
		if(s=='-')f=-f;
		s=getchar_unlocked();
	}
	do{
		x=(x<<1)+(x<<3)+(s^48);
		s=getchar_unlocked();
	}while(isdigit(s));
	x*=f;
	*w=x;
}
void write(long long x){
	if(x<0)x=-x,putchar_unlocked(45);
	if(x>9)write(x/10);
	putchar_unlocked(x%10+48);
}
const int MOD = 998244353;
ll N, ans, q, len, cont;
int main() {
    read(&N);
    for (ll i = 1; i <= N;) {
        q = N / i;
        len = (N / q) - i + 1;
        cont = len % MOD * ((q % MOD) * (q % MOD) % MOD) % MOD;
        ans = (ans + cont) % MOD;
        i = (N / q) + 1;
    }
    write(ans);
}
