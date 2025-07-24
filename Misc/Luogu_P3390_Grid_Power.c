//
// Created by 118 on 2025/7/7.
//
#include<stdio.h>
const int MOD=1e9+7;
long long n,k;
typedef struct{
    long long mat[101][101];
}Matrix;
Matrix a,b;
Matrix times(Matrix a,Matrix b) {
    Matrix c;
    for (int i=1;i<=n;++i) {
        for (int j=1;j<=n;++j) {
            c.mat[i][j]=0;
        }
    }
    for (int i=1;i<=n;++i) {
        for (int k=1;k<=n;++k) {
            for (int j=1;j<=n;++j) {
                c.mat[i][j]+=a.mat[i][k]*b.mat[k][j];
                c.mat[i][j]%=MOD;
            }
        }
    }
    return c;
}
int main() {
    scanf("%lld%lld",&n,&k);
    for(int i=1;i<=n;++i) {
        for(int j=1;j<=n;++j) {
            scanf("%lld",&a.mat[i][j]);
        }
        b.mat[i][i]=1;
    }
    while (k) {
        if (k&1) {
            b=times(a,b);
        }
        a=times(a,a);
        k>>=1;
    }
    for (int i=1;i<=n;++i) {
        for (int j=1;j<=n;++j) {
            printf("%lld ",b.mat[i][j]);
        }
        putchar(10);
    }
}
//孩子们，我被 JetBrains CLion 强制改格式了