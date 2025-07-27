#pragma GCC optimize(2,3,"Ofast")
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
int readLL(ll*w){
	ll f=1,x=0;
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
void writeLL(ll x){
	if(x<0){
		x=-x;
		putchar_unlocked(45);
	}
	if(x>9)writeLL(x/10);
	putchar_unlocked(x%10+48);
}
long long min(long long a,long long b){
	return a<b?a:b;
}
int n,m,a,b,k,D[501],has[501],q,op,x,y;
ll d[501][501],c,t,bestd[501],T;
void add(int u,int v,ll w){
	for(int i=0;i<n;++i){
		if(d[i][u]==4e18&&d[i][v]==4e18){
			continue;
		}
		for(int j=0;j<n;++j){
			ll alt1=d[i][u]+w+d[v][j],alt2=d[i][v]+w+d[u][j];
			ll cand=min(alt1,alt2);
			if(cand<d[i][j]){
				d[i][j]=cand;
			}
		}
	}
}
int main(){
	readInt(&n);
	readInt(&m);
	for(int i=0;i<n;++i){
		for(int j=0;j<n;++j){
			d[i][j]=4e18;
		}
		d[i][i]=0;
		bestd[i]=4e18;
	}
	for(int i=0;i<m;++i){
		readInt(&a);
		readInt(&b);
		readLL(&c);
		--a;
		--b;
		d[a][b]=min(d[a][b],c);
		d[b][a]=min(d[b][a],c);
	}
	readInt(&k);
	readLL(&T);
	for(int i=0;i<k;++i){
		readInt(&D[i]);
		--D[i];
		has[D[i]]=1;
		bestd[D[i]]=0;
	}
	for(int kk=0;kk<n;++kk){
		for(int i=0;i<n;++i){
			if(d[i][kk]==4e18){
				continue;
			}
			for(int j=0;j<n;++j){
				ll via=d[i][kk]+d[kk][j];
				if(via<d[i][j]){
					d[i][j]=via;
				}
			}
		}
	}
	for(int i=0;i<n;++i){
		if(has[i]){
			for(int j=0;j<n;++j){
				bestd[j]=min(bestd[j],d[j][i]);
			}
		}
	}
	readInt(&q);
	while(q--){
		readInt(&op);
		if(op==1){
			readInt(&x);
			readInt(&y);
			readLL(&t);
			--x;
			--y;
			add(x,y,t);
			for(int i=0;i<n;++i){
				if(has[i]){
					for(int j=0;j<n;++j){
						bestd[j]=min(bestd[j],d[j][i]);
					}
				}
			}
		}
		else if(op==2){
			readInt(&x);
			--x;
			if(!has[x]){
				has[x]=1;
				bestd[x]=0;
				for(int i=0;i<n;++i){
					bestd[i]=min(bestd[i],d[i][x]);
				}
			}
		}
		else{
			ll ans = 0;
			int anyAirport=0;
			for(int i=0;i<n;++i){
				if(bestd[i]<4e18){
					anyAirport=1;
					break;
				}
			}
			for(int i=0;i<n;++i){
				for(int j=0;j<n;++j){
					ll viaRoad=d[i][j];
					ll val=(viaRoad<4e18?viaRoad:0);
					if(anyAirport){
						ll viaAir=bestd[i]+bestd[j];
						if(viaAir<4e18){
							viaAir+=T;
							if(viaAir<viaRoad||viaRoad==4e18){
								val=viaAir;
							}
						}
					}
					ans+=val;
				}
			}
			writeLL(ans);
			putchar_unlocked(10);
		}
	}
}
