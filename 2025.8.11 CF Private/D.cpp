//
// Created by 118 on 25-8-1.
//
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
const int P_max = 10000;
struct Node {
    int l, r, mid;
    vector<vector<int>> vl;
    vector<vector<int>> vr;
    Node *left_child, *right_child;
};
Node* build(int l, int r, vector<int>& p, vector<int>& v) {
    Node *node = new Node();
    node->l = l;
    node->r = r;
    node->mid = (l + r) / 2;
    int left_total = node->mid - l + 1;
    int right_total = r - node->mid;

    if (left_total > 0) {
        node->vl.resize(left_total, vector<int>(P_max + 1, 0));
        int pos0 = node->mid;
        for (int j = 0; j <= P_max; j++) {
            if (j >= p[pos0]) {
                node->vl[0][j] = v[pos0];
            } else {
                node->vl[0][j] = 0;
            }
        }
        for (int j = 1; j <= P_max; j++) {
            node->vl[0][j] = max(node->vl[0][j], node->vl[0][j - 1]);
        }
        for (int i = 1; i < left_total; i++) {
            int pos = node->mid - i;
            for (int j = 0; j <= P_max; j++) {
                node->vl[i][j] = node->vl[i - 1][j];
            }
            for (int j = P_max; j >= p[pos]; j--) {
                if (node->vl[i - 1][j - p[pos]] + v[pos] > node->vl[i][j]) {
                    node->vl[i][j] = node->vl[i - 1][j - p[pos]] + v[pos];
                }
            }
            for (int j = 1; j <= P_max; j++) {
                node->vl[i][j] = max(node->vl[i][j], node->vl[i][j - 1]);
            }
        }
    }
    if (right_total > 0) {
        node->vr.resize(right_total, vector<int>(P_max + 1, 0));
        int pos0 = node->mid + 1;
        if (pos0 <= r) {
            for (int j = 0; j <= P_max; j++) {
                if (j >= p[pos0]) {
                    node->vr[0][j] = v[pos0];
                } else {
                    node->vr[0][j] = 0;
                }
            }
            for (int j = 1; j <= P_max; j++) {
                node->vr[0][j] = max(node->vr[0][j], node->vr[0][j - 1]);
            }
            for (int i = 1; i < right_total; i++) {
                int pos = node->mid + 1 + i;
                if (pos > r) break;
                for (int j = 0; j <= P_max; j++) {
                    node->vr[i][j] = node->vr[i - 1][j];
                }
                for (int j = P_max; j >= p[pos]; j--) {
                    if (node->vr[i - 1][j - p[pos]] + v[pos] > node->vr[i][j]) {
                        node->vr[i][j] = node->vr[i - 1][j - p[pos]] + v[pos];
                    }
                }
                for (int j = 1; j <= P_max; j++) {
                    node->vr[i][j] = max(node->vr[i][j], node->vr[i][j - 1]);
                }
            }
        }
    }
    if (l < r) {
        node->left_child = build(l, node->mid, p, v);
        node->right_child = build(node->mid + 1, r, p, v);
    }
    else {
        node->left_child = nullptr;
        node->right_child = nullptr;
    }
    return node;
}
int query(Node* node, int L, int R, int P) {
    if (L > R) return 0;
    if (node->l == node->r) {
        return node->vl[0][P];
    }
    if (L <= node->mid && R >= node->mid + 1) {
        int left_len = node->mid - L + 1;
        int right_len = R - node->mid;
        vector<int>& left_backpack = node->vl[left_len - 1];
        vector<int> right_backpack_vector;
        if (right_len > 0) {
            right_backpack_vector = node->vr[right_len - 1];
        }
        else {
            right_backpack_vector = vector<int>(P_max + 1, 0);
        }
        int ans = 0;
        for (int x = 0; x <= P; x++) {
            int y = P - x;
            if (y > P_max) y = P_max;
            int value = left_backpack[x] + right_backpack_vector[y];
            if (value > ans) ans = value;
        }
        return ans;
    }
    if (R <= node->mid) {
        return query(node->left_child, L, R, P);
    }
    if (L >= node->mid + 1) {
        return query(node->right_child, L, R, P);
    }
    return 0;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    vector<int> p(n);
    vector<int> v(n);
    for (int i = 0; i < n; i++) {
        cin >> p[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }
    Node* root = build(0, n - 1, p, v);
    int Q;
    cin >> Q;
    int last = 0;
    for (int i = 0; i < Q; i++) {
        int iL, iR, iP;
        cin >> iL >> iR >> iP;
        int L = (iL + last) % n;
        int R = (iR + last) % n;
        int P_val = (iP + last) % 10000;
        L++;
        R++;
        P_val++;
        if (L > R) {
            swap(L, R);
        }
        last = query(root, L - 1, R - 1, P_val);
        cout << last << '\n';
    }
}