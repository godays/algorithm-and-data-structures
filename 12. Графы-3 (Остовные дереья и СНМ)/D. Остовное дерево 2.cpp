#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct edge {
    int a = 0;
    int b = 0;
    int w = 0;

    bool operator()(edge ad, edge bd) {
        return ad.w < bd.w;
    }
};

int n, m;
vector<edge> r_w;
vector<int> parent, len;

int find_set(int v) {
    if (v == parent[v])
        return v;
    parent[v] = find_set(parent[v]);
    return parent[v];
}

void union_sets(int a, int b) {
    a = find_set(a);
    b = find_set(b);
    if (a != b) {
        if (len[a] < len[b])
            swap(a, b);
        parent[b] = a;
        len[a] += len[b];
    }
}

int main() {
    cin >> n >> m;
    int a, b, c;
    r_w.resize(m);
    parent.resize(n + 1);
    len.resize(n + 1);

    for (int i = 0; i <= n; i++) {
        parent[i] = i;
        len[i] = 1;
    }

    for (int i = 0; i < m; i++) {
        cin >> a >> b >> c;
        if (a == b)
            continue;
        r_w[i].a = min(a, b);
        r_w[i].b = max(a, b);
        r_w[i].w = c;
    }

    long long ans = 0;

    sort(r_w.begin(), r_w.end(), edge());
    for (auto & i : r_w) {
        a = find_set(i.a);
        b = find_set(i.b);
        if (a != b) {
            union_sets(i.a, i.b);
            ans += i.w;
        }
    }
    cout << ans;
    return 0;
}