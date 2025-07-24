#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <algorithm>
#include <climits>
using namespace std;

const int MAX = 1000000;
vector<int> min_prime;

void precompute_min_prime() {
    min_prime.resize(MAX + 1, 0);
    vector<int> primes;
    for (int i = 2; i <= MAX; i++) {
        if (min_prime[i] == 0) {
            min_prime[i] = i;
            primes.push_back(i);
        }
        for (size_t j = 0; j < primes.size(); j++) {
            int p = primes[j];
            if (p > min_prime[i] || 1LL * i * p > MAX) break;
            min_prime[i * p] = p;
        }
    }
}

int normalize(int x) {
    if (x == 0) return 1;
    int sign = 1;
    if (x < 0) {
        sign = -1;
        x = -x;
    }
    int res = 1;
    while (x > 1) {
        int p = min_prime[x];
        int cnt = 0;
        while (x % p == 0) {
            cnt++;
            x /= p;
        }
        if (cnt & 1) {
            res *= p;
        }
    }
    return sign * res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    precompute_min_prime();

    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    vector<int> norm(n);
    for (int i = 0; i < n; i++) {
        norm[i] = normalize(a[i]);
    }

    map<int, int> count_map;
    for (int v : norm) {
        count_map[v]++;
    }

    int ans = INT_MAX;

    if (count_map.find(1) != count_map.end() && count_map[1] >= 1) {
        ans = 1;
    }

    for (const auto& [v, cnt] : count_map) {
        if (v != 1 && cnt >= 2) {
            ans = min(ans, 2);
        }
    }

    set<int> primes_set;
    primes_set.insert(0);
    vector<int> one_prime, two_prime, three_more;

    for (int v : norm) {
        if (v == 1) continue;
        int temp = abs(v);
        vector<int> factors;
        if (v < 0) {
            factors.push_back(-1);
        }
        while (temp > 1) {
            int p = min_prime[temp];
            factors.push_back(p);
            int cnt = 0;
            while (temp % p == 0) {
                cnt++;
                temp /= p;
            }
        }
        if (factors.size() == 1 || factors.size() == 2) {
            for (int p : factors) {
                primes_set.insert(p);
            }
        }
    }

    vector<int> nodes(primes_set.begin(), primes_set.end());
    int tot = nodes.size();
    map<int, int> prime_to_index;
    for (int i = 0; i < tot; i++) {
        prime_to_index[nodes[i]] = i;
    }

    vector<vector<int>> graph(tot);
    set<pair<int, int>> edges_added;

    for (int v : norm) {
        if (v == 1) continue;
        vector<int> factors;
        int temp = abs(v);
        if (v < 0) {
            factors.push_back(-1);
        }
        while (temp > 1) {
            int p = min_prime[temp];
            factors.push_back(p);
            int cnt = 0;
            while (temp % p == 0) {
                cnt++;
                temp /= p;
            }
        }

        if (factors.size() == 1) {
            int p = factors[0];
            if (prime_to_index.find(p) == prime_to_index.end()) continue;
            int idx_p = prime_to_index[p];
            int idx0 = prime_to_index[0];
            int u = min(idx0, idx_p);
            int v = max(idx0, idx_p);
            if (edges_added.find({u, v}) == edges_added.end()) {
                edges_added.insert({u, v});
                graph[u].push_back(v);
                graph[v].push_back(u);
            }
        } else if (factors.size() == 2) {
            int p1 = factors[0], p2 = factors[1];
            if (prime_to_index.find(p1) == prime_to_index.end() || prime_to_index.find(p2) == prime_to_index.end()) continue;
            int idx1 = prime_to_index[p1];
            int idx2 = prime_to_index[p2];
            int u = min(idx1, idx2);
            int v = max(idx1, idx2);
            if (edges_added.find({u, v}) == edges_added.end()) {
                edges_added.insert({u, v});
                graph[u].push_back(v);
                graph[v].push_back(u);
            }
        }
    }

    int min_cycle = INT_MAX;
    for (int start = 0; start < tot; start++) {
        if (min_cycle <= 3) break;
        vector<int> dist(tot, -1);
        vector<int> parent(tot, -1);
        queue<int> q;
        dist[start] = 0;
        q.push(start);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            if (dist[u] * 2 + 1 >= min_cycle) {
                break;
            }
            for (int v : graph[u]) {
                if (v == parent[u]) continue;
                if (dist[v] == -1) {
                    dist[v] = dist[u] + 1;
                    parent[v] = u;
                    q.push(v);
                } else {
                    min_cycle = min(min_cycle, dist[u] + dist[v] + 1);
                }
            }
        }
    }

    if (min_cycle != INT_MAX) {
        ans = min(ans, min_cycle);
    }

    if (ans == INT_MAX) {
        cout << -1 << endl;
    } else {
        cout << ans << endl;
    }

    return 0;
}
