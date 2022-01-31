#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> res(n, vector<int>(m));
    vector<vector<pair<int, int>>> parents(n, vector<pair<int, int>>(m));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> res[i][j];
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (i == 0 && j == 0)
                continue;

            if (i > 0 && j > 0) {
                if (res[i - 1][j] > res[i][j - 1]) {
                    res[i][j] += res[i - 1][j];
                    parents[i][j] = {i - 1, j};
                } else {
                    res[i][j] += res[i][j - 1];
                    parents[i][j] = {i, j - 1};
                }
            } else if (j > 0) {
                res[i][j] += res[i][j - 1];
                parents[i][j] = {i, j - 1};
            } else {
                res[i][j] += res[i - 1][j];
                parents[i][j] = {i - 1, j};
            }
        }
    }

    vector<char> ans;

    cout << res[n - 1][m - 1] << '\n';
    int i = n - 1;
    int j = m - 1;
    while (i > 0 || j > 0) {
        int new_i = parents[i][j].first;
        int new_j = parents[i][j].second;
        if (new_i == i)
            ans.push_back('R');
        else
            ans.push_back('D');
        i = new_i;
        j = new_j;
    }

    for (int i = ans.size() - 1; i >= 0; i--) {
        cout << ans[i];
    }
    return 0;
}

