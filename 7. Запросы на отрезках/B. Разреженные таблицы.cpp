#include <iostream>
#include <vector>

using namespace std;

const int A = 23;
const int P = 21563;
const int M = 16714589;

int hash_a(int a_prev) {
    return (A * a_prev + P) % M;
}

int main() {
    int n, m, a_1;
    int u, v;
    cin >> n >> m >> a_1;
    cin >> u >> v;

    vector<int> lg(n + 1, 0);
    for (int i = 2; i <= n; i++) {
        lg[i] = lg[i - 1];
        if ((1 << (lg[i] + 1)) <= i)
            lg[i]++;
    }

    vector<vector<int>> min_dp(n, vector<int>(lg[n] + 1));

    int cur_a = a_1;
    int prev_a = a_1;
    min_dp[0][0] = a_1;
    for (int i = 1; i < n; i++) {
        cur_a = hash_a(prev_a);
        min_dp[i][0] = cur_a;
        prev_a = cur_a;
    }

    for (int j = 1; (1 << j) <= n; j++) {
        for (int i = 0; (i + (1 << j) - 1) < n; i++) {
            min_dp[i][j] = min(min_dp[i][j - 1], min_dp[i + (1 << (j - 1))][j - 1]);
        }
    }

    for (int i = 1; i <= m; i++) {
        u--;
        v--;
        bool flag = false;
        if (u > v) {
            swap(u, v);
            flag = true;
        }
        int j = (int) (lg[v - u + 1]);

        int ans_i = min(min_dp[u][j], min_dp[v - (1 << j) + 1][j]);
        if (flag)
            swap(u, v);
        if (i == m)
            cout << u + 1 << " " << v + 1 << " " << ans_i;

        u = ((17 * (u + 1) + 751 + ans_i + 2 * i) % n) + 1;
        v = ((13 * (v + 1) + 593 + ans_i + 5 * i) % n) + 1;
    }
    return 0;
}
