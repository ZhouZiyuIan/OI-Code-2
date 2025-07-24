#pragma GCC optimize(3,"Ofast") 
#include<stdio.h>
typedef long long ll;
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
int readInt(int*w) {
	int f=1,x=0;
	char s=getchar_unlocked();
	while(!isdigit(s)) {
		if(s=='-')f=-f;
		else if(s==-1)return 0;
		s=getchar_unlocked();
	}
	do {
		x=(x<<1)+(x<<3)+(s^48);
		s=getchar_unlocked();
	}while(isdigit(s));
	x*=f;
	*w=x;
	return 1;
}
int readLL(ll*w) {
	ll f=1,x=0;
	char s=getchar_unlocked();
	while(!isdigit(s)) {
		if(s=='-')f=-f;
		else if(s==-1)return 0;
		s=getchar_unlocked();
	}
	do {
		x=(x<<1)+(x<<3)+(s^48);
		s=getchar_unlocked();
	}while(isdigit(s));
	x*=f;
	*w=x;
	return 1;
}
void writeLL(ll x) {
	if(x<0) {
		x=-x;
		putchar_unlocked(45);
	}
	if(x>9)writeLL(x/10);
	putchar_unlocked(x%10+48);
}
int T;
ll a,b,c,d,a1,b1,c1,x0,y0,kmin,kmax,kx,ky,f,m;
ll abs(ll x){return x<0?-x:x;}
ll min(ll a,ll b){return a<b?a:b;}
ll max(ll a,ll b){return a>b?a:b;}
ll exgcd(ll a,ll b,ll*x,ll*y) {
	if(b==0){
		*x=(a<0)?-1:1;
		*y=0;
		return abs(a);
	}
	ll d=exgcd(b,a%b,y,x);
	*y-=a/b**x;
	return d;
}
ll gcd(ll a,ll b) {
	if (b==0)return abs(a);
	return gcd(abs(b),abs(a)%abs(b));
}
ll floor_div(ll a,ll b) {
	if (b==0)return 0;
	ll d=a/b;
	if (a%b==0)return d;
	if ((a<0)^(b<0))return d-1;
	else return d;
}
ll ceil_div(ll a,ll b) {
	if (b==0)return 0;
	ll d=a/b;
	if (a%b==0)return d;
	if ((a<0)^(b<0))return d;
	else return d+1;
}
ll min_positive(ll a,ll MOD) {
	if (MOD<=0)return 0;
	ll r=a%MOD;
	if (r<0)r+=MOD;
	if (r==0)return MOD;
	return r;
}
int main() {
	readInt(&T);
	while (T--) {
		readLL(&a);
		readLL(&b);
		readLL(&c);
		if (a==0&&b==0&&c!=0) {
			putchar_unlocked(45);
			putchar_unlocked(49);
			putchar_unlocked(10);
			continue;
		}
		if (a==0&&b==0&&c==0) {
			putchar_unlocked(73);
			putchar_unlocked(78);
			putchar_unlocked(70);
			putchar_unlocked(32);
			putchar_unlocked(49);
			putchar_unlocked(32);
			putchar_unlocked(49);
			putchar_unlocked(32);
			putchar_unlocked(73);
			putchar_unlocked(78);
			putchar_unlocked(70);
			putchar_unlocked(32);
			putchar_unlocked(73);
			putchar_unlocked(78);
			putchar_unlocked(70);
			putchar_unlocked(10);
			continue;
		}
		d=gcd(a,b);
		if (c%d) {
			putchar_unlocked(45);
			putchar_unlocked(49);
			putchar_unlocked(10);
			continue;
		}
		a1=a/d;
		b1=b/d;
		c1=c/d;
		if (b1==0) {
			if (a1==1) {
				if (c1>0) {
					putchar_unlocked(73);
					putchar_unlocked(78);
					putchar_unlocked(70);
					putchar_unlocked(32);
					writeLL(c1);
					putchar_unlocked(32);
					putchar_unlocked(49);
					putchar_unlocked(32);
					writeLL(c1);
					putchar_unlocked(32);
					putchar_unlocked(73);
					putchar_unlocked(78);
					putchar_unlocked(70);
					putchar_unlocked(10);
				}
				else {
					writeLL(c1);
					putchar_unlocked(32);
					putchar_unlocked(49);
					putchar_unlocked(10);
				}
			}
			else if (a1==-1) {
				if (c1<0) {
					putchar_unlocked(73);
					putchar_unlocked(78);
					putchar_unlocked(70);
					putchar_unlocked(32);
					writeLL(-c1);
					putchar_unlocked(32);
					putchar_unlocked(49);
					putchar_unlocked(32);
					writeLL(-c1);
					putchar_unlocked(32);
					putchar_unlocked(73);
					putchar_unlocked(78);
					putchar_unlocked(70);
					putchar_unlocked(10);
				}
				else {
					writeLL(-c1);
					putchar_unlocked(32);
					putchar_unlocked(49);
					putchar_unlocked(10);
				}
			}
			continue;
		}
		if (a1==0) {
			if (b1==1) {
				if (c1>0) {
					putchar_unlocked(73);
					putchar_unlocked(78);
					putchar_unlocked(70);
					putchar_unlocked(32);
					putchar_unlocked(49);
					putchar_unlocked(32);
					writeLL(c1);
					putchar_unlocked(32);
					putchar_unlocked(73);
					putchar_unlocked(78);
					putchar_unlocked(70);
					putchar_unlocked(32);
					writeLL(c1);
					putchar_unlocked(10);
				}
				else {
					putchar_unlocked(49);
					putchar_unlocked(32);
					writeLL(c1);
					putchar_unlocked(10);
				}
			}
			else if (b1==-1) {
				if (c1<0) {
					putchar_unlocked(73);
					putchar_unlocked(78);
					putchar_unlocked(70);
					putchar_unlocked(32);
					putchar_unlocked(49);
					putchar_unlocked(32);
					writeLL(-c1);
					putchar_unlocked(32);
					putchar_unlocked(73);
					putchar_unlocked(78);
					putchar_unlocked(70);
					putchar_unlocked(32);
					writeLL(-c1);
					putchar_unlocked(10);
				}
				else {
					putchar_unlocked(49);
					putchar_unlocked(32);
					writeLL(-c1);
					putchar_unlocked(10);
				}
			}
			continue;
		}
		d=exgcd(abs(a1),abs(b1),&x0,&y0);
		if (a1<0)x0=-x0;
		if (b1<0)y0=-y0;
		x0*=c1;
		y0*=c1;
		if (a1*b1>0) {
			if (a1<0&&b1<0) {
				a1=-a1;
				b1=-b1;
			}
			kmin=ceil_div(1-x0,b1);
			kmax=floor_div(y0-1,a1);
			if (kmin<=kmax) {
				writeLL(kmax-kmin+1);
				putchar_unlocked(32);
				writeLL(x0+b1*kmin);
				putchar_unlocked(32);
				writeLL(y0-a1*kmax);
				putchar_unlocked(32);
				writeLL(x0+b1*kmax);
				putchar_unlocked(32);
				writeLL(y0-a1*kmin);
				putchar_unlocked(10);
			}
			else {
				writeLL(min_positive(x0,abs(b1)));
				putchar_unlocked(32);
				writeLL(min_positive(y0,abs(a1)));
				putchar_unlocked(10);
			}
		}
		else {
			if (a1>0&&b1<0) {
                kx=floor_div(x0-1,-b1);
                ky=floor_div(y0-1,a1);
                kmax=min(kx,ky);
				putchar_unlocked(73);
				putchar_unlocked(78);
				putchar_unlocked(70);
				putchar_unlocked(32);
				writeLL(x0+b1*kmax);
				putchar_unlocked(32);
				writeLL(y0-a1*kmax);
				putchar_unlocked(32);
				putchar_unlocked(73);
				putchar_unlocked(78);
				putchar_unlocked(70);
				putchar_unlocked(32);
				putchar_unlocked(73);
				putchar_unlocked(78);
				putchar_unlocked(70);
				putchar_unlocked(10);
			}
			else {
                kx=ceil_div(1-x0,b1);
                ky=ceil_div(1-y0,-a1);
                kmin=max(kx,ky);
                putchar_unlocked(73);
				putchar_unlocked(78);
				putchar_unlocked(70);
				putchar_unlocked(32);
				writeLL(x0+b1*kmin);
				putchar_unlocked(32);
				writeLL(y0-a1*kmin);
				putchar_unlocked(32);
				putchar_unlocked(73);
				putchar_unlocked(78);
				putchar_unlocked(70);
				putchar_unlocked(32);
				putchar_unlocked(73);
				putchar_unlocked(78);
				putchar_unlocked(70);
				putchar_unlocked(10);
			}
		}
	}
}

