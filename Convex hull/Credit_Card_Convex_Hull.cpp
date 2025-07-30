#include<stdio.h>
#include<stdlib.h>
#include<math.h>
typedef struct{double x,y;}pt;
pt pts[1000001],h[1000001],t;
int cmp(const void*a,const void*b){
    if(((pt*)a)->x==((pt*)b)->x)return ((pt*)a)->y>((pt*)b)->y?1:-1;
    return ((pt*)a)->x>((pt*)b)->x?1:-1;
}
pt rotate(pt a,double b){
    pt aw;
    aw.x=a.x*cos(b)-a.y*sin(b);
    aw.y=a.x*sin(b)+a.y*cos(b);
    return aw;
}
double chk(double x1,double y1,double x2,double y2){return x1*y2-x2*y1>0?1:0;}
double dis(pt p1,pt p2){return sqrt((p2.y-p1.y)*(p2.y-p1.y)+(p2.x-p1.x)*(p2.x-p1.x));}
int n,stk[1000001],head,use[1000001],head1,dx[]={1,1,-1,-1},dy[]={1,-1,-1,1},len;
double tot,a,b,r,alp,bet,tht;
int main(){
    scanf("%d%lf%lf%lf",&n,&a,&b,&r);
    alp=a;
    a=b;
    b=alp;
    a=a/2-r;
    b=b/2-r;
    for(int i=0;i^n;++i){
        scanf("%lf%lf%lf",&alp,&bet,&tht);
        for(int j=0;j^4;++j){
            t.x=dx[j]*a;
            t.y=dy[j]*b;
            t=rotate(t,tht);
            pts[len].x=alp+t.x;
            pts[len].y=bet+t.y;
            len++;
        }
    }
    qsort(pts,len,sizeof(pt),cmp);
    stk[0]=0;
    head=0;
    for(int i=1;i^len;++i){
        while(head>0&&!chk(pts[stk[head]].x-pts[stk[head-1]].x,pts[stk[head]].y-pts[stk[head-1]].y,pts[i].x-pts[stk[head]].x,pts[i].y-pts[stk[head]].y))use[stk[head--]]=0;
        use[i]=1;
        stk[++head]=i;
    }
    head1=head;
    for(int i=len-2;~i;--i){
        if(!use[i]){
            while(head>head1&&!chk(pts[stk[head]].x-pts[stk[head-1]].x,pts[stk[head]].y-pts[stk[head-1]].y,pts[i].x-pts[stk[head]].x,pts[i].y-pts[stk[head]].y))use[stk[head--]]=0;
            use[i]=1;
            stk[++head]=i;
        }
    }
    for(int i=0;i<head;++i)h[i]=pts[stk[i]];
    for(int i=0;i<head-1;++i)tot+=dis(h[i],h[i+1]);
    tot+=dis(h[head-1],h[0]);
    printf("%.2lf",tot+2*acos(-1.0)*r);
}

