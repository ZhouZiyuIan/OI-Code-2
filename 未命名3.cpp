#include <stdio.h>
#include <map>
#include <set>
#include <vector>
#include <algorithm>
using namespace std;
int T, lens;
bool fix(vector<vector<int> >& groups, map<int, set<int> >& inGroup) {
    int k = groups.size();
    while (true) {
        vector<int> odds;
        for (int i = 0; i < k; ++i) {
            if (groups[i].size() & 1) odds.push_back(i);
        }
        if (odds.empty()) break;
        bool moved = false;
        for (int a = 0; a + 1 < (int)odds.size() && !moved; ++a) {
            for (int b = a + 1; b < (int)odds.size() && !moved; ++b) {
                int g1 = odds[a], g2 = odds[b];
                for (int idx = 0; idx < (int)groups[g1].size(); ++idx) {
                    int x = groups[g1][idx];
                    if (inGroup[x].count(g2) == 0) {
                        groups[g1].erase(groups[g1].begin() + idx);
                        groups[g2].push_back(x);
                        inGroup[x].erase(g1);
                        inGroup[x].insert(g2);
                        moved = true;
                        break;
                    }
                }
                if (moved) break;
                for (int idx = 0; idx < (int)groups[g2].size(); ++idx) {
                    int x = groups[g2][idx];
                    if (inGroup[x].count(g1) == 0) {
                        groups[g2].erase(groups[g2].begin() + idx);
                        groups[g1].push_back(x);
                        inGroup[x].erase(g2);
                        inGroup[x].insert(g1);
                        moved = true;
                        break;
                    }
                }
            }
        }
        if (!moved) return false;
    }
    return true;
}
bool chk(int k, const vector<int>& S) {
    map<int,int> cnt;
    for (int x : S) ++cnt[x];
    for (auto& p : cnt) {
        if (p.second > k) return false;
    }
    vector<vector<int>> groups(k);
    map<int, set<int>> inGroup;
    vector<int> nums;
    for (auto& p : cnt) nums.push_back(p.first);
    sort(nums.begin(), nums.end());
    int idx = 0;
    for (int x : nums) {
        int f = cnt[x];
        inGroup[x].clear();
        for (int i = 0; i < f; ++i) {
            groups[idx % k].push_back(x);
            inGroup[x].insert(idx % k);
            ++idx;
        }
    }
    if (!fix(groups, inGroup)) return false;
    for (int i = 0; i < k; ++i) {
        if (groups[i].size() % 2 != 0 || groups[i].empty()) return false;
    }
    printf("%d\n", k);
    for (auto& grp : groups) {
        printf("%d", (int)grp.size());
        for (int x : grp) {
            printf(" %d", x);
        }
        putchar('\n');
    }
    return true;
}
int main() {
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &lens);
        vector<int> S(lens);
        for (int i = 0; i < lens; ++i) {
            scanf("%d", &S[i]);
        }
        if (lens & 1) {
            puts("-1");
            continue;
        }
        map<int,int> cnt;
        int cmax = 0;
        for (int x : S) {
            int f = ++cnt[x];
            if (f > cmax) cmax = f;
        }
        bool suc = false;
        for (int k = cmax; k <= lens; ++k) {
            if (chk(k, S)) {
                suc = true;
                break;
            }
        }
        if (!suc) {
            puts("-1");
        }
    }
    return 0;
}