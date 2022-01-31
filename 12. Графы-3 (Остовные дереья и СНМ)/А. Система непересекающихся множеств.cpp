#include <iostream>
#include <vector>
#include <string>

using namespace std;

int n;
vector<int> prev_;
vector<int> rank_;
vector<int> cnt;
vector<int> max_;
vector<int> min_;

void init() {
    prev_.resize(n);
    rank_.resize(n);
    cnt.resize(n);
    max_.resize(n);
    min_.resize(n);

    for (int i = 0; i < n; i++) {
        prev_[i] = i;
        rank_[i] = 0;
        min_[i] = i + 1;
        max_[i] = i + 1;
        cnt[i] = 1;
    }
}

int get(int x) {
    if (prev_[x] != x)
        prev_[x] = get(prev_[x]);
    return prev_[x];
}

vector<int> get_all(int x) {
    int p = get(x);
    vector<int> res{min_[p], max_[p], cnt[p]};

    return res;
}

void join(int x, int y) {
    x = get(x);
    y = get(y);
    if (x == y)
        return;

    if (rank_[x] > rank_[y])
        swap(x, y);
    if (rank_[x] == rank_[y])
        rank_[y]++;

    prev_[x] = y;
    min_[y] = min(min_[x], min_[y]);
    max_[y] = max(max_[x], max_[y]);
    cnt[y] += cnt[x];
}

int main() {
    cin >> n;
    init();

    string cmd;

    while (cin >> cmd) {
        if (cmd == "union") {
            int x, y;
            cin >> x >> y;
            join(x - 1, y - 1);
        } else if (cmd == "get") {
            int x;
            cin >> x;
            vector<int> res = get_all(x - 1);
            cout << res[0] << " " << res[1] << " " << res[2] << '\n';
        }
    }
    return 0;
}
