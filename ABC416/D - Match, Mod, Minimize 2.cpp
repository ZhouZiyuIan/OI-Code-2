#include <cstdio>
#include <set>
using namespace std;
int T,n,m,a[300001],b[300001];
long long ans,cont,ds;
int main(){
	scanf("%d",&T);
	for(int t=0;t<T;++t){
		scanf("%d%d",&n,&m);
		for(int i=0;i<n;++i){
			scanf("%d",&a[i]);
		}
		for(int i=0;i<n;++i){
			scanf("%d",&b[i]);
		}
		ans=0;
		multiset<long long>ms(a,a+n);
		for(int i=0;i<n;++i){
			ds=m-b[i];
			auto it=ms.lower_bound(ds);
			if(it==ms.end()){
				it=ms.begin();
			}
			cont=*it+b[i];
			if(cont>=m)cont-=m;
			ans+=cont;
			ms.erase(it);
		}
		printf("%lld\n",ans);
	}
}
