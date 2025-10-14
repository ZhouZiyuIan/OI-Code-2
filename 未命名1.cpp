#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXN = 5e5 + 5;
struct Item {
    int value, price;
} items[MAXN];

int n, T;
ll m;

bool check(vector<Item>& selected_items, int mid_value, int q) {
    if (selected_items.size() < q) return false;
    
    vector<Item> larger, smaller;
    for (const auto& item : selected_items) {
        if (item.value >= mid_value) larger.push_back(item);
        else smaller.push_back(item);
    }

    int need_larger = (q + 1) / 2;
    if (larger.size() < need_larger) return false;

    // Try all possible combinations of items that have value >= mid_value
    sort(larger.begin(), larger.end(), 
         [](const Item& a, const Item& b) { return a.price < b.price; });
    
    ll total_cost = 0;
    for (int i = 0; i < need_larger; i++) {
        total_cost += larger[i].price;
    }

    int remaining = q - need_larger;
    if (remaining > 0) {
        sort(smaller.begin(), smaller.end(), 
             [](const Item& a, const Item& b) { return a.price < b.price; });
        for (int i = 0; i < remaining && i < smaller.size(); i++) {
            total_cost += smaller[i].price;
        }
    }

    return total_cost <= m && remaining <= smaller.size();
}

int solve(int q) {
    if (q > n || q % 2 == 0) return -1;
    
    vector<Item> valid_items;
    for (int i = 0; i < n; i++) {
        valid_items.push_back(items[i]);
    }

    // Binary search on the median value
    int left = 0, right = 1e6 + 1;
    int ans = -1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (check(valid_items, mid, q)) {
            ans = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin >> n >> m >> T;
    for (int i = 0; i < n; i++) {
        cin >> items[i].value >> items[i].price;
    }

    while (T--) {
        int q;
        cin >> q;
        cout << solve(q) << '\n';
    }

    return 0;
}