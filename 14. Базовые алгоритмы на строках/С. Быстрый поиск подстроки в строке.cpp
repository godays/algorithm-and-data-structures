#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<int> prefixFun(string s) {
    int n = s.length();
    vector<int> prefix(n, 0);


    for (int i = 1; i < n; ++i) {
        int j = prefix[i - 1];
        while (j > 0 && s[i] != s[j])
            j = prefix[j - 1];
        if (s[i] == s[j])
            j++;
        prefix[i] = j;
    }
    return prefix;
}

void KMP(string p, string t) {
    vector<int> prefix = prefixFun(p + "#" + t);
    vector<int> res;
    int p_len = p.length();
    int t_len = t.length();

    for (int i = p_len; i < p_len + 1 + t_len; ++i)
        if (prefix[i] == p_len)
            res.push_back(i - p_len * 2 + 1);

    cout << res.size() << '\n';
    for (int i: res)
        cout << i << ' ';
}

int main() {
    string p, t;
    cin >> p >> t;

    KMP(p, t);
    return 0;
}
