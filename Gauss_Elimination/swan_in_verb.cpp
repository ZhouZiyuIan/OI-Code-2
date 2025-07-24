//
// Created by 118 on 25-7-24.
//
#pragma GCC optimize(3, "Ofast")
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#ifdef _WIN64
#define getchar_unlocked() _getchar_nolock()
#define putchar_unlocked(_c) _putchar_nolock(_c)
#endif
void readInt(int*w){
	int f=1,x=0;
	char s=getchar_unlocked();
	while(!isdigit(s)){
		if(s=='-')f=-f;
		s=getchar_unlocked();
	}
	do{
		x=(x<<1)+(x<<3)+(s^48);
		s=getchar_unlocked();
	}while(isdigit(s));
	x*=f;
	*w=x;
}
int n, m, u[125001], v[125001], head[501], nxt[250001], to[250001], cnt, deg[501];
double a[501][501], b[501], x[501], f[125001], ans;
void add(const int u, const int v) {
	nxt[++cnt] = head[u];
	to[cnt] = v;
	head[u] = cnt;
}
void gauss() {
	for (int i = 1; i < n; ++i) {
		int p = i;
		for (int k = i + 1; k < n; ++k) {
			if (abs(a[k][i]) > abs(a[p][i])) {
				p = k;
			}
		}
		if (i != p) {
			double tmp;
			for (int j = 0; j <= n + 1; ++j) {
				tmp = a[i][j];
				a[i][j] = a[p][j];
				a[p][j] = tmp;
			}
			for (int j = 0; j <= n + 1; ++j) {
				tmp = b[i];
				b[i] = b[p];
				b[p] = tmp;
			}
		}
		for (int k = i + 1; k < n; ++k) {
			double d = a[k][i] / a[i][i];
			b[k] -= d * b[i];
			for (int j = i; j < n; ++j) {
				a[k][j] -= d * a[i][j];
			}
		}
	}
	for(int i = n - 1;i >= 1; --i) {
		for (int j = i + 1; j < n; ++j) {
			b[i] -= x[j] * a[i][j];
		}
		x[i] = b[i] / a[i][i];
	}
}
int cmp(const void *a,const void *b) {
	return (*(double *) a >= *(double *) b) ? 1 : -1;
}
int main() {
	readInt(&n);
	readInt(&m);
	for (int i = 1; i <= m; ++i) {
		readInt(&u[i]);
		readInt(&v[i]);
		add(u[i], v[i]);
		add(v[i], u[i]);
		++deg[u[i]];
		++deg[v[i]];
	}
	for (int u = 1; u < n; ++u) {
		a[u][u] = 1.0;
		for (int i = head[u]; i; i = nxt[i]) {
			int v = to[i];
			if(v != n) {
				a[u][v] = -1.0 / deg[v];
			}
		}
	}
	b[1] = 1.0;
	gauss();
	for (int i = 1; i <= m; ++i) {
		if (u[i] != n) {
			f[i] += x[u[i]] / deg[u[i]];
		}
		if (v[i] != n) {
			f[i] += x[v[i]] / deg[v[i]];
		}
	}
	qsort(f, m + 1, sizeof(double), cmp);
	for (int i = 1; i <= m; ++i) {
		ans += (m - i + 1) * f[i];
	}
	printf("%.3lf\n", ans);
}