#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> dp(n);
    vector<int> p(n);
    vector<int> seq(n);

    for (int i = 0; i < n; i++)
        cin >> seq[i];

    dp[0] = 1;
    p[0] = -1;

    for (int i = 1; i < n; i++) {
        int max_len = 0;
        int max_p = 0;
        for (int j = i - 1; j >= 0; j--) {
            if (seq[j] < seq[i]) {
                if (dp[j] > max_len) {
                    max_len = dp[j];
                    max_p = j;
                }
            }
        }
        p[i] = max_p;
        dp[i] = max_len + 1;
    }

    int max_len = 0;
    int max_index = 0;

    for (int i = 0; i < n; i++) {
        if (dp[i] > max_len) {
            max_len = dp[i];
            max_index = i;
        }
    }

    int len = dp[max_index];
    vector<int> ans;

    cout << len << '\n';

    while (len > 0) {
        ans.push_back(seq[max_index]);
        max_index = p[max_index];
        len--;
    }

    for (int i = ans.size() - 1; i >=0; i--)
        cout << ans[i] << " ";

    return 0;
}

