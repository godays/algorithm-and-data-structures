#include <iostream>
#include <vector>

using namespace std;

bool can_cut(vector<int> lens, int k, int len) {
    int cnt = 0;

    for (int cur_len: lens) {
        cnt += cur_len / len;
        if (cnt >= k)
            return true;
    }

    return false;
}

int main() {
    int n;
    int k;
    int l = 0;
    int r;
    cin >> n >> k;
    vector<int> lens(n);

    for (int i = 0; i < n; i++) {
        cin >> lens[i];
        if (lens[i] > r)
            r = lens[i];
    }

    while (l < r - 1) {
        int m = (l + r) / 2;
        if (can_cut(lens, k, m))
            l = m;
        else
            r = m;
    }

    cout << l;
    return 0;
}
