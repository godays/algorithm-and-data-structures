#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<int> zFunction(string s) {
    int n = s.length();
    vector<int> z(n, 0);

    int left = 0;
    int right = 0;

    for (int i = 1; i < n; ++i) {
        if (i <= right)
            z[i] = min(right - i + 1, z[i - left]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]])
            z[i]++;
        if (i + z[i] - 1 > right) {
            left = i;
            right = i + z[i] - 1;
        }
    }
    return z;
}

int main() {
    string s;
    cin >> s;

    vector<int> ans = zFunction(s);

    for (int i = 1; i < ans.size(); ++i)
        cout << ans[i] << ' ';
    return 0;
}
