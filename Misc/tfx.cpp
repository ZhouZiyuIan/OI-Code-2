#include<bits/stdc++.h>
#define endl '\n'
using namespace std;
const int N = 55;
const double eps = 1e-9;
double ans[N];
double a[N][N];
int n;
signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	cin >> n;
	for (int i = 1; i <= n; i++) for (int j = 1; j <= n + 1; j++) cin >> a[i][j];
	int w = 1;
	for (int i = 1; i <= n + 1; i++) {
		int r = w;
		for (int j = w + 1; j <= n; j++) if (abs(a[j][i]) > fabs(a[r][i])) r = j;
		if (abs(a[r][i]) <= eps) continue;
		if (r != w){
			for(int j = i;j <= n + 1;j++)swap(a[w][j], a[r][j]);
		}
		double div = a[w][i];
		for (int j = i; j <= n + 1; j++) a[w][j] /= div;
		for (int j = 1; j <= n; j++) {
			double div = a[j][i];
			if(j == w)continue;
			for (int k = n + 1; k >= i; k--) a[j][k] -= div * a[w][k];
		}
		w++;
	}
	if(abs(a[w-1][n])<=eps){
        cout<<-1;
        return 0;
    }
    if(n+1-w>0){
        cout<<0;
        return 0; 
    }
	for (int i = 1; i <= n; i++) {
		cout << "x" << i << "=";
		cout << fixed << setprecision(2) << a[i][n + 1] << endl;
	}
	return 0;
}
