#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<long long> T;
vector<int> a;
int n;

int Fen(int i) {
    return i & (i + 1);
}

long long get(int i) {
    long long res = 0;
    while (i >= 0) {
        res += T[i];
        i = Fen(i) - 1;
    }
    return res;
}

void add(int i, int x) {
    int j = i;
    while (j < n) {
        T[j] += x;
        j = j | (j + 1);
    }
}

void set(int i, int x) {
    int delta = x - a[i];
    a[i] = x;
    add(i, delta);
}

long long rsq(int l, int r) {
    if (l == 0)
        return get(r);
    return get(r) - get(l - 1);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n;
    T.assign(n, 0);
    a.assign(n, 0);

    for (int i = 0; i < n; i++)
        cin >> a[i];

    for (int i = 0; i < n; i++)
        add(i, a[i]);

    string command;

    while (cin >> command) {
        if (command == "set") {
            int ind;
            int x;
            cin >> ind >> x;
            set(ind - 1, x);
        }
        else if (command == "sum") {
            int ind_i;
            int ind_j;
            cin >> ind_i >> ind_j;
            cout << rsq(ind_i - 1, ind_j - 1) << "\n";
        }
    }
    return 0;
}
