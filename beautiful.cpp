#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct DSU {
    int n;
    vector<int> p, sz, L, R;
    DSU(int n=0): n(n), p(n+1,-1), sz(n+1,0), L(n+1,0), R(n+1,0) {}
    void make(int x){ p[x]=x; sz[x]=1; L[x]=R[x]=x; }
    int find(int x){ return p[x]==x?x:p[x]=find(p[x]); }
    void unite(int a,int b){
        a=find(a); b=find(b); if(a==b) return;
        if(sz[a]<sz[b]) swap(a,b);
        p[b]=a; sz[a]+=sz[b]; L[a]=min(L[a],L[b]); R[a]=max(R[a],R[b]);
    }
    int size(int x){ return sz[find(x)]; }
    int leftmost(int x){ return L[find(x)]; }
    int rightmost(int x){ return R[find(x)]; }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n; if(!(cin>>n)) return 0;
    vector<int> h(n+1);
    vector<int> pos(n+1);
    for(int i=1;i<=n;i++){ cin>>h[i]; pos[h[i]] = i; }

    vector<char> marked(n+2, 0);
    DSU dsu(n);
    set<int> S; // marked positions set, include sentinels 0 and n+1
    S.insert(0); S.insert(n+1);
    ll curSum = 0;
    auto compute_b = [&](int i)->ll{
        if(i<1 || i>n-1) return 0;
        if(!marked[i]) return 0;
        if(marked[i+1]) return 0;
        // left size = size of marked component containing i
        int left_root = dsu.find(i);
        ll left_size = dsu.sz[left_root];
        // next marked to right of i
        auto it = S.upper_bound(i);
        int posR = *it; // >i
        ll right_size = posR - i - 1; // number of unmarked starting at i+1
        if(right_size<=0) return 0;
        return left_size * right_size;
    };

    ll answer = 0;
    for(int val=1; val<=n; ++val){
        int p = pos[val];
        // subtract old contributions at boundaries p-1 and p
        curSum -= compute_b(p-1);
        curSum -= compute_b(p);
        // mark p
        marked[p]=1;
        dsu.make(p);
        // insert into set
        S.insert(p);
        // union with left and right if marked
        if(p-1>=1 && marked[p-1]) dsu.unite(p, p-1);
        if(p+1<=n && marked[p+1]) dsu.unite(p, p+1);
        // add new contributions
        curSum += compute_b(p-1);
        curSum += compute_b(p);
        // add to total
        answer += curSum;
    }
    cout<<answer<<"\n";
    return 0;
}

