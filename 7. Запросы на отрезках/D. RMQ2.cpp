#include <iostream>
#include <vector>
#include <climits>

using namespace std;

long long const INF = LONG_LONG_MAX;

struct Node {
    long long data = INF;
    long long add = 0;
    long long set = INF;
    long long l;
    long long r;
    bool up = false;

    Node() {}

    Node(long long d, long long a, long long s, long left, long right, bool u) {
        data = d;
        add = a;
        set = s;
        l = left;
        r = right;
        up = u;
    }
};

vector<Node> tree;
vector<long long> a;
int n;

void build(int v, int tl, int tr) {
    if (tl == tr) {
        tree[v] = Node(a[tl], 0, a[tl], tl, tr, false);
    } else {
        int tm = tl + (tr - tl) / 2;
        build(v * 2, tl, tm);
        build(v * 2 + 1, tm + 1, tr);
        tree[v] = Node(min(tree[2 * v].data, tree[2 * v + 1].data), 0, 0, tl, tr, false);
        tree[v].set = tree[v].data;
    }
}

void push_set(int v) {
    if (!tree[v].up)
        return;

    tree[v].data = tree[v].set;
    tree[v].up = false;

    if (tree[v].l == tree[v].r)
        return;

    tree[v * 2].set = tree[v].set;
    tree[v * 2 + 1].set = tree[v].set;
    tree[v * 2].up = true;
    tree[v * 2 + 1].up = true;
    tree[v * 2].add = 0;
    tree[v * 2 + 1].add = 0;
}

void push(int v) {
    push_set(v);
    if (tree[v].add == 0)
        return;

    tree[v].data += tree[v].add;
    tree[v].set = tree[v].data;

    long long addi = tree[v].add;
    tree[v].add = 0;

    if (tree[v].l == tree[v].r)
        return;

    tree[2 * v].add += addi;
    tree[2 * v + 1].add += addi;
}

void update_set(int v, long long value, int l, int r) {
    if (tree[v].r < l || tree[v].l > r)
        return;

    if (tree[v].r <= r && tree[v].l >= l) {
        tree[v].add = 0;
        push_set(v);

        tree[v].set = value;
        tree[v].up = true;

        return;
    }
    push(v);

    update_set(2 * v, value, l, r);
    update_set(2 * v + 1, value, l, r);

    tree[v].data = min(tree[v * 2].set + tree[v * 2].add, tree[v * 2 + 1].set + tree[v * 2 + 1].add);
    tree[v].set = tree[v].data;
}

void update_add(int v, long long value, int l, int r) {
    if (tree[v].r < l || tree[v].l > r)
        return;

    if (tree[v].r <= r && tree[v].l >= l) {
        push(v);
        tree[v].add = value;
        return;
    }

    push(v);

    update_add(2 * v, value, l, r);
    update_add(2 * v + 1, value, l, r);

    tree[v].data = min(tree[v * 2 + 1].set + tree[v * 2 + 1].add, tree[v * 2].set + tree[v * 2].add);
    tree[v].set = tree[v].data;
}

long long get(int v, int l, int r) {
    if (tree[v].r < l || tree[v].l > r)
        return INF;

    if (tree[v].r <= r && tree[v].l >= l) {
        push(v);
        return tree[v].data;
    }
    push(v);
    return min(get(v * 2, l, r), get(v * 2 + 1, l, r));
}

int main() {
    cin >> n;
    a.resize(n);
    tree.resize(4 * n);

    for (int i = 0; i < n; i++)
        cin >> a[i];

    build(1, 0, n - 1);
    string cmd;
    while (cin >> cmd) {
        int l, r;
        long long x;

        if (cmd == "min") {
            cin >> l >> r;
            cout << get(1, l - 1, r - 1) << "\n";
        }

        if (cmd == "set") {
            cin >> l >> r >> x;
            update_set(1, x, l - 1, r - 1);
        }

        if (cmd == "add") {
            cin >> l >> r >> x;
            update_add(1, x, l - 1, r - 1);
        }
    }

    return 0;
}