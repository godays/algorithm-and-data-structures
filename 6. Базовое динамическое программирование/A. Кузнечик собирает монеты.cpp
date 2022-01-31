#include <iostream>
#include <vector>

using namespace std;

int const MIN_COST = -10001;

struct Node {
    int price = 0;
    int jump_num = 0;
    vector<int> path;
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    int k;
    cin >> n >> k;
    vector<int> price(n, 0);
    vector<Node> res(n);

    for (int i = 1; i < n - 1; i++)
        cin >> price[i];

    res[0] = {0, 0, {0}};

    for (int i = 1; i < n; i++) {
        int best_jump = MIN_COST;
        int best_jump_ind = i;
        for (int j = 1; j <= k && i - j >= 0; j++) {
            if (price[i] + res[i - j].price > best_jump || best_jump == MIN_COST) {
                best_jump = res[i - j].price + price[i];
                best_jump_ind = i - j;
            }
        }
        res[i].price = res[best_jump_ind].price + price[i];
        res[i].jump_num = res[best_jump_ind].jump_num + 1;
        for (auto p: res[best_jump_ind].path) {
            res[i].path.push_back(p);
        }
        res[i].path.push_back(i);
    }
    cout << res[n - 1].price << "\n" << res[n - 1].jump_num << '\n';
    for (auto p: res[n - 1].path) {
        cout << p + 1 << " ";
    }
    return 0;
}


