#include<stdio.h>
#include<stdlib.h>
typedef struct{double x,y;}pt;
pt pts[1000001], h[1000001];
int cmp(const void*a,const void*b){
	if(((pt*)a)->x==((pt*)b)->x)return ((pt*)a)->y>((pt*)b)->y?1:-1;
	return ((pt*)a)->x>((pt*)b)->x?1:-1;
}
double cross(double x1,double y1,double x2,double y2){return x1*y2-x2*y1;}
int sol(pt* p,int n){
	for(int i=0;i<n;i++)if(cross(p[i].x-p[(i-1+n)%n].x,p[i].y-p[(i-1+n)%n].y,p[(i+1)%n].x-p[i].x,p[(i+1)%n].y-p[i].y)&&cross(p[(i+1)%n].x-p[i].x,p[(i+1)%n].y-p[i].y,p[(i+2)%n].x-p[(i+1)%n].x,p[(i+2)%n].y-p[(i+1)%n].y))return 0;
	return 1;
}
int t, n, stk[1000001], head, use[1000001], head1;
double tot;
main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		for(int i=0;i<n;++i)scanf("%lf%lf",&pts[i].x,&pts[i].y);
		if(n<6){
			puts("NO");
			continue;
		}
		qsort(pts,n,sizeof(pt),cmp);
		head=0;
		stk[++head]=0;
		for(int i=1;i<n;++i){
			while(head>1&&cross(pts[stk[head]].x-pts[stk[head-1]].x,pts[stk[head]].y-pts[stk[head-1]].y,pts[i].x-pts[stk[head]].x,pts[i].y-pts[stk[head]].y)<0)use[stk[head--]]=0;
			use[i]=1;
			stk[++head]=i;
		}
		head1=head;
		for(int i=n-2;~i;--i){
			while(head>head1&&cross(pts[stk[head]].x-pts[stk[head-1]].x,pts[stk[head]].y-pts[stk[head-1]].y,pts[i].x-pts[stk[head]].x,pts[i].y-pts[stk[head]].y)<0)use[stk[head--]]=0;
			use[i]=1;
			stk[++head]=i;
		}
		for(int i=1;i<=head;++i)h[i-1]=pts[stk[i]];
		puts(sol(h,head)?"YES":"NO");
	}
}
