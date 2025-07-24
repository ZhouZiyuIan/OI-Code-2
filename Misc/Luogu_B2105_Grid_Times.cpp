//
// Created by 118 on 2025/7/7.
//
#include<stdio.h>
int n,m,k,a[101][101],b[101][101],t;
int main() {
    scanf("%d%d%d",&n,&m,&k);
    for (int i=0;i<n;++i) {
        for (int j=0;j<m;++j) {
            scanf("%d",&a[i][j]);
        }
    }
    for (int i=0;i<m;++i) {
        for (int j=0;j<k;++j) {
            scanf("%d",&b[i][j]);
        }
    }
    for (int i=0;i<n;++i) {
        for (int j=0;j<k;++j) {
            t=0;
            for (int l=0;l<m;++l) {
                t+=a[i][l]*b[l][j];
            }
            printf("%d ",t);
        }
        putchar(10);
    }
}