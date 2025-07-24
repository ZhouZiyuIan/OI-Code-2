#pragma GCC optimize(3,"Ofast")
#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#ifdef _WIN64
#define getchar_unlocked() _getchar_nolock()
#define putchar_unlocked(_c) _putchar_nolock(_c)
#endif
#define lowbit(x) (x & -x)
void cmax(int* a, const int b) {
	*a < b ? *a = b : 0;
}
void read(int* w) {
	int f = 1, x = 0;
	char s = getchar_unlocked();
	while (!isdigit(s)) {
		if(s == '-') {
			f = -f;
		}
		s = getchar_unlocked();
	}
	do{
		x = (x << 1) + (x << 3) + (s ^ 48);
		s = getchar_unlocked();
	} while(isdigit(s));
	x *= f;
	*w = x;
}
void write(int x){
	if (x < 0) {
		x = -x;
		putchar_unlocked(45);
	}
	if (x > 9) {
		write(x / 10);
	}
	putchar_unlocked(x % 10 + 48);
}
int n, u, v, w, head[400001], cnt, mx[400001], tot, ans, siz[400001], vis[400001], root, k, rev[400001], dis[400001],f[400001];
typedef struct {
	int to,val,nxt;
} edg;
edg e[800001];
int cmp(const void *a,const void *b){return (*(int*)a-*(int*)b);}
void add(int from, int to, int dis) {
	e[++cnt].nxt = head[from];
	e[cnt].to = to;
	e[cnt].val = dis;
	head[from] = cnt;
}
void get_root(const int u, const int fa) {
	siz[u] = 1;
	mx[u] = 0;
	for (int i = head[u], v = e[i].to; i; v = e[i = e[i].nxt].to) {
		if(v == fa || vis[v]) continue;
		get_root(v, u);
		siz[u] += siz[v];
		cmax(&mx[u], siz[v]);
	}
	cmax(&mx[u], tot - siz[u]);
	if (mx[u] < mx[root]) {
		root = u;
	}
}
void getdis(const int u, const int fa) {
	rev[++ tot] = dis[u];
	for (int i = head[u], v = e[i].to; i; v = e[i = e[i].nxt].to) {
		if(v == fa || vis[v]) continue;
		dis[v] = dis[u] + e[i].val;
		getdis(v, u);
	}
}
int fun(int u, int w) {
	tot = 0;
	dis[u] = w;
	getdis(u, 0);
	qsort(rev, tot + 1, sizeof(int), cmp);
	int l = 1, r = tot, ans = 0;
	while(l <= r) {
		if (rev[l] + rev[r] <= k) {
			ans += r - l;
			++l;
		}
		else {
			--r;
		}
	}
	return ans;
}
void sol(int u) {
	vis[u] = 1;
	ans += fun(u, 0);
	for (int i = head[u], v = e[i].to; i; v = e[i = e[i].nxt].to) {
		if(vis[v]) continue;
		ans -= fun(v, e[i].val);
		tot = siz[v];
		mx[0] = n;
		root = 0;
		get_root(v, u);
		sol(root);
	}
}
int main() {
	read(&n);
	for (int i = 1; i < n; ++i) {
		read(&u);
		read(&v);
		read(&w);
		add(u, v, w);
		add(v, u, w);
	}
	read(&k);
	tot = mx[0] = n;
	get_root(1, 0);
	sol(1);
	write(ans);
}