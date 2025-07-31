#include<stdio.h>
#include<stdlib.h>
typedef struct{double x,y;}pt;
pt pts[1000001], h[1000001];
int cmp(const void*a,const void*b){
	if(((pt*)a)->x==((pt*)b)->x)return ((pt*)a)->y>((pt*)b)->y?1:-1;
	return ((pt*)a)->x>((pt*)b)->x?1:-1;
}
double chk(double x1,double y1,double x2,double y2){return x1*y2-x2*y1>0?1:0;}
int n, stk[1000001], head, use[1000001], head1;
double tot;
main(){
	scanf("%d", &n);
	for(int i=0;i<n;++i)scanf("%lf%lf",&pts[i].x,&pts[i].y);
	qsort(pts,n,sizeof(pt),cmp);
	stk[++head]=0;
	for(int i=1;i<n;++i){
		while(head>1&&!chk(pts[stk[head]].x-pts[stk[head-1]].x,pts[stk[head]].y-pts[stk[head-1]].y,pts[i].x-pts[stk[head]].x,pts[i].y-pts[stk[head]].y))use[stk[head--]]=0;
		use[i]=1;
		stk[++head]=i;
	}
	head1=head;
	for(int i=n-2;~i;--i){
		while(head>head1&&!chk(pts[stk[head]].x-pts[stk[head-1]].x,pts[stk[head]].y-pts[stk[head-1]].y,pts[i].x-pts[stk[head]].x,pts[i].y-pts[stk[head]].y))use[stk[head--]]=0;
		use[i]=1;
		stk[++head]=i;
	}
	for(int i=1;i<=head;++i)h[i-1]=pts[stk[i]];
	for(int i=0;i<head-1;++i)tot+=h[i].x*h[i+1].y-h[i+1].x*h[i].y;
	tot/=2;
	printf("%.2lf",tot);
}
