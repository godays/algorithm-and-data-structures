#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
    string source;
    string target;

    cin >> source >> target;

    if (source.size() > target.size())
        swap(source, target);

    int min_size = source.size();
    int max_size = target.size();
    vector<int> dp(min_size + 1);

    for (int i = 0; i <= min_size; i++)
        dp[i] = i;

    for (int j = 1; j <= max_size; j++) {
        int prev = dp[0];
        int prev_tmp;
        dp[0]++;

        for (int i = 1; i <= min_size; i++) {
            prev_tmp = dp[i];
            if (source[i - 1] == target[j - 1])
                dp[i] = prev;
            else
                dp[i] = min(min(dp[i - 1], dp[i]), prev) + 1;
            prev = prev_tmp;
        }
    }

    cout << dp[min_size];
    return 0;
}

