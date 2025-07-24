//
// Created by 118 on 25-7-7.
//
#include <stdio.h>
#include <string.h>
int n,q,m,a[100001],tree[400001],mul[400001],op,x,y,k;
void build(int k,int l,int r) {
    if (l==r) {
        tree[k]=a[l];
        mul[k]=1;
        return;
    }
    int mid=(l+r)>>1;
    build(k<<1,l,mid);
    build(k<<1|1,mid+1,r);
    tree[k]=tree[k<<1]+tree[k<<1|1];
    mul[k]=mul[k<<1]*mul[k<<1|1];
    tree[k]%=m;
}
int main() {
    scanf("%d%d%d",&n,&q,&m);
    for (int i=1;i<=n;++i) {
        scanf("%d",&a[i]);
    }
    build(1,1,n);
    while (q--) {
        scanf("%d%d%d",&op,&x,&y);
        if (op==3) {
            //TODO:
        }
    }
}