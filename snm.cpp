#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
using namespace std;
 
// Try to fix parity by swapping between groups.
// groups: vector of groups (each group is a vector<int> of elements)
// inGroup[x]: for each distinct element x, the set of groups indices in which x occurs.
bool fix_parity(vector<vector<int>> &groups, unordered_map<int, unordered_set<int>> &inGroup) {
    int k = groups.size();
    bool changed = true;
    while(changed) {
        changed = false;
        // collect indices of groups with odd size
        vector<int> odds;
        for (int i = 0; i < k; i++) {
            if(groups[i].size() % 2 == 1)
                odds.push_back(i);
        }
        if(odds.empty()) break;
        // Try every pair of odd groups
        bool donePair = false;
        for (int a = 0; a < odds.size() && !donePair; a++) {
            for (int b = a+1; b < odds.size() && !donePair; b++) {
                int g1 = odds[a], g2 = odds[b];
                // Try to find an element x in g1 that is not in g2.
                // Then we can remove x from g1 and assign it to g2.
                for (int x : groups[g1]) {
                    if(inGroup[x].count(g2)==0) {
                        // swap assignment of x: remove from g1, add to g2.
                        // Remove one occurrence x from group g1.
                        bool removed = false;
                        for(auto it = groups[g1].begin(); it != groups[g1].end(); it++){
                            if(*it == x){
                                groups[g1].erase(it);
                                removed = true;
                                break;
                            }
                        }
                        // add x to group g2.
                        groups[g2].push_back(x);
                        // update inGroup for x.
                        inGroup[x].erase(g1);
                        inGroup[x].insert(g2);
                        changed = true; // parity of both groups flipped.
                        donePair = true;
                        break;
                    }
                }
            }
        }
        if(!changed) break; // no swap found, cannot fix further.
    }
    // Check if all groups  have even size.
    for (int i = 0; i < k; i++) {
        if(groups[i].size() % 2 == 1)
            return false;
    }
    return true;
}
 
// Main solver: Try to partition S into k groups (each group even sized and with distinct numbers)
// Returns true if success; groups holds the sets.
bool try_k(int k, const vector<int> &S) {
    int n = S.size();
    // For each distinct element, count frequency.
    unordered_map<int, int> freq;
    for (int x : S) freq[x]++;
 
    // Check: k must be at least each frequency.
    for(auto &p: freq){
        if(p.second > k)
            return false;
    }
 
    // Prepare groups: k groups initially empty.
    vector<vector<int>> groups(k);
    // For each distinct element, assign its freq copies to groups 0..(freq-1)
    // Also maintain, for each element, in which groups it appears.
    unordered_map<int, unordered_set<int>> inGroup;
    for(auto &p : freq) {
        int x = p.first;
        int f = p.second;
        inGroup[x] = unordered_set<int>();
        // assign copy to groups 0..f-1 (natural assignment)
        for(int i = 0; i < f; i++){
            groups[i].push_back(x);
            inGroup[x].insert(i);
        }
    }
 
    // Now try to fix parity by swapping occurrences between groups.
    if(!fix_parity(groups, inGroup)) return false;
 
    // Final check: every group must be nonempty and even.
    for(int i = 0; i < k; i++){
        if(groups[i].empty() || groups[i].size() % 2 == 1)
            return false;
    }
 
    // Output solution.
    cout << k << "\n";
    for(auto &grp : groups){
        cout << grp.size();
        for (int x : grp)
            cout << " " << x;
        cout << "\n";
    }
    return true;
}
 
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
 
    int T; cin >> T;
    while(T--){
        int n; cin >> n;
        vector<int> S(n);
        for (int i = 0; i < n; i++){
            cin >> S[i];
        }
 
        // Total size must be even.
        if(n % 2 == 1) {
            cout << -1 << "\n";
            continue;
        }
 
        // Compute frequency and maximum freq.
        unordered_map<int,int> freq;
        for (int x : S) freq[x]++;
        int fmax = 0;
        for(auto &p: freq) {
            if(p.second > fmax)
                fmax = p.second;
        }
 
        // Also note: maximum possible groups is n/2 (because each group has at least 2 elements).
        bool solved = false;
        for(int k = fmax; k <= n/2; k++){
            if(try_k(k, S)){
                solved = true;
                break;
            }
        }
 
        if(!solved)
            cout << -1 << "\n";
    }
    return 0;
}