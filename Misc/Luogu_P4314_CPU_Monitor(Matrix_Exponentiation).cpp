//
// Created by 118 on 25-7-7.
//
#include <cstdio>
const long long inf=1e14;
int T,E,x,y;
char op[1];
bool hav[600001];
template <typename T>
inline T max(T a, T b) {
    return a < b ? b : a;
}
struct vec {
    long long a,b,z;
}tree[600001];
struct mat {
    long long a0,a1,a2,a3;
    inline void init() {
        a0=0;
        a1=a2=a3=-inf;
    }
}tag[600001],add,chg,fre;
inline vec operator + (const vec x,const vec y) {
    vec res;
    res.a=max(x.a,y.a);
    res.b=max(x.b,y.b);
    res.z=0;
    return res;
}
inline vec operator * (const mat x,const vec y) {
    vec res;
    res.a=max(x.a0+y.a,x.a1);
    res.b=max(x.a2+y.a,max(x.a3,y.b));
    res.z=0;
    return res;
}
inline mat operator * (const mat x,const mat y) {
    mat res;
    res.a0=x.a0+y.a0;
    res.a1=max(x.a0+y.a1,x.a1);
    res.a2=max(x.a2+y.a0,y.a2);
    res.a3=max(x.a2+y.a1,max(y.a3,x.a3));
    return res;
}
inline void pushdown(int k) {
    if (!hav[k]) {
        return;
    }
    tree[k<<1]=tag[k]*tree[k<<1];
    tag[k<<1]=tag[k]*tag[k<<1];
    hav[k<<1]=true;
    tree[k<<1|1]=tag[k]*tree[k<<1|1];
    tag[k<<1|1]=tag[k]*tag[k<<1|1];
    hav[k<<1|1]=true;
    hav[k]=0;
    tag[k].init();
}
inline void plus(int k,int l,int r,int L,int R) {
    if (L<=l&&r<=R) {
        tree[k]=add*tree[k];
        tag[k]=add*tag[k];
        hav[k]=1;
        return;
    }
    pushdown(k);
    int mid=(l+r)>>1;
    if (L<=mid) {
        plus(k<<1,l,mid,L,R);
    }
    if (R>mid) {
        plus(k<<1|1,mid+1,r,L,R);
    }
    tree[k]=tree[k<<1]+tree[k<<1|1];
}
inline void modify(int k,int l,int r,int L,int R) {
    if (L<=l&&r<=R) {
        tree[k]=chg*tree[k];
        tag[k]=chg*tag[k];
        hav[k]=1;
        return;
    }
    pushdown(k);
    int mid=(l+r)>>1;
    if (L<=mid) {
        modify(k<<1,l,mid,L,R);
    }
    if (R>mid) {
        modify(k<<1|1,mid+1,r,L,R);
    }
    tree[k]=tree[k<<1]+tree[k<<1|1];
}
inline long long que_cur(int k,int l,int r,int L,int R) {
    if (L<=l&&r<=R) {
        return tree[k].a;
    }
    pushdown(k);
    int mid=(l+r)>>1;
    long long res=-inf;
    if (L<=mid) {
        res=max(res,que_cur(k<<1,l,mid,L,R));
    }
    if (R>mid) {
        res=max(res,que_cur(k<<1|1,mid+1,r,L,R));
    }
    return res;
}
inline long long que_hist(int k,int l,int r,int L,int R) {
    if (L<=l&&r<=R) {
        return tree[k].b;
    }
    pushdown(k);
    int mid=(l+r)>>1;
    long long res=-inf;
    if (L<=mid) {
        res=max(res,que_hist(k<<1,l,mid,L,R));
    }
    if (R>mid) {
        res=max(res,que_hist(k<<1|1,mid+1,r,L,R));
    }
    return res;
}
void build(int k,int l,int r) {
    tag[k].init();
    if (l==r) {
        scanf("%lld",&tree[k].a);
        tree[k].b=tree[k].a;
        return;
    }
    int mid=(l+r)>>1;
    build(k<<1,l,mid);
    build(k<<1|1,mid+1,r);
    tree[k]=tree[k<<1]+tree[k<<1|1];
}
int main() {
    scanf("%d",&T);
    build(1,1,T);
    add.init();
    chg.init();
    fre.init();
    chg.a0=-inf;
    fre.a2=0;
    scanf("%d",&E);
    while (E--) {
        scanf("%s%d%d",op,&x,&y);
        if (op[0]=='Q') {
            printf("%lld\n",que_cur(1,1,T,x,y));
        }
        else if (op[0]=='A') {
            printf("%lld\n",que_hist(1,1,T,x,y));
        }
        else if (op[0]=='P') {
            scanf("%lld",&add.a0);
            plus(1,1,T,x,y);
        }
        else {
            scanf("%lld",&chg.a1);
            modify(1,1,T,x,y);
        }
        tree[1]=fre*tree[1];
        tag[1]=fre*tag[1];
        hav[1]=1;
    }
}
//被 JetBrains Clion 改码风改疯了