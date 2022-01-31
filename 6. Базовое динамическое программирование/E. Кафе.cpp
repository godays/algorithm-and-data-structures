#include <iostream>
#include <vector>

using namespace std;

int const INF = 1000000;
vector<vector<int>> ans;
vector<int> price;

int dp(int i, int j) {
    if (j > i)
        return INF;

    int res;
    int cost = price[i];

    if (j <= 0) {
        if (i >= 1) {
            if (cost <= 100) {
                int dif = min(dp(i - 1, j + 1), dp(i - 1, j) + cost);
                res = dif;
            } else
                return dp(i - 1, j + 1);
        } else
            return 0;
    } else {
        if (ans[i][j] != -1)
            return ans[i][j];
        if (cost > 100) {
            int dif = min(dp(i - 1, j + 1), dp(i - 1, j - 1) + cost);
            res = dif;
        } else {
            int dif = min(dp(i - 1, j + 1), dp(i - 1, j) + cost);
            res = dif;
        }
    }
    ans[i][j] = res;
    return res;
}

void find_best(vector<int>& used, int i, int j) {
    if (j < i) {
        int cost = price[i];
        if (j <= 0) {
            if (i >= 1) {
                if (cost > 100) {
                    used.push_back(i);
                    find_best(used, i - 1, j + 1);
                } else {
                    bool added_i = (dp(i, j) == dp(i - 1, j + 1));
                    if (added_i) {
                        used.push_back(i);
                        find_best(used, i - 1, j + 1);
                    } else
                        find_best(used, i - 1, j);
                }
            }
        } else {
            if (cost <= 100) {
                bool added_i = (dp(i - 1, j + 1) == dp(i, j));
                if (added_i) {
                    used.push_back(i);
                    find_best(used, i - 1, j + 1);
                } else
                    find_best(used, i - 1, j);
            } else {
                bool added_i = (dp(i - 1, j + 1) == dp(i, j));
                if (added_i) {
                    used.push_back(i);
                    find_best(used, i - 1, j + 1);
                } else
                    find_best(used, i - 1, j - 1);
            }
        }
    }
}

int main() {
    int n;
    int k1 = 0;
    int k2 = 0;
    cin >> n;
    price = vector<int>(n + 1);
    ans = vector<vector<int>>(n + 1, vector<int>(n + 2));

    for (int i = 1; i <= n; i++)
        cin >> price[i];

    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= n + 1; j++)
            ans[i][j] = -1;

    int res = INF;

    for (int i = 0; i <= n; i++) {
        if (res >= dp(n, i)) {
            res = dp(n, i);
            k1 = i;
        }
    }

    vector<int> used;

    find_best(used, n, k1);
    k2 = used.size();

    cout << res << '\n' << k1 << " " << k2 << '\n';

    while (!used.empty()) {
        cout << used.back() << '\n';
        used.pop_back();
    }

    return 0;
}

