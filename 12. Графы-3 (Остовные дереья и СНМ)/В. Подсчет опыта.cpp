#include <iostream>
#include <vector>
#include <string>

using namespace std;

int n;
int m;
vector<int> p;
vector<int> sizes;
vector<int> exp;


void init() {
    p.resize(n);
    sizes.assign(n, 1);
    exp.assign(n, 0);

    for (int i = 0; i < n; i++)
        p[i] = i;
}

pair<int, int> get_func(int x) {
    if (p[x] != x) {
        auto tmp = get_func(p[x]);
        int exp_delta = tmp.first;
        int parent_x = tmp.second;
        if (parent_x != p[x]) {
            p[x] = parent_x;
            exp[x] += exp_delta;
        }
        return {exp[x], p[x]};
    }
    return {0, p[x]};
}

int get_exp(int x) {
    if (x == p[x])
        return exp[x];
    int p_x = get_func(x).second;
    return exp[p_x] + exp[x];
}

void join(int x, int y) {
    x = get_func(x).second;
    y = get_func(y).second;

    if (x == y)
        return;

    if (sizes[x] > sizes[y])
        swap(x, y);

    p[x] = y;
    sizes[y] += sizes[x];
    exp[x] -= exp[y];
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m;
    init();

    string cmd;

    for (int i = 0; i < m; i++) {
        cin >> cmd;
        if (cmd == "join") {
            int x, y;
            cin >> x >> y;

            join(x - 1, y - 1);
        } else if (cmd == "get") {
            int x;
            cin >> x;

            cout << get_exp(x - 1) << '\n';
        } else if (cmd == "add") {
            int x, v;
            cin >> x >> v;

            int head = get_func(x - 1).second;
            exp[head] += v;
        }
    }
    return 0;
}
