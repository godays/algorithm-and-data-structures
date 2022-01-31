#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int lower_bound(const int& x, const vector<int>& vec) {
    int l = -1;
    int r = vec.size();

    while (l < r - 1) {
        int mid = (r + l) / 2;

        if (x <= vec[mid])
            r = mid;
        else
            l = mid;
    }
    return r;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    int k;
    cin >> n;
    vector<int> vec(n);

    for (int i = 0; i < n; i++)
        cin >> vec[i];

    cin >> k;

    sort(vec.begin(), vec.end());

    for (int i = 0; i < k; i++) {
        int l, r;
        cin >> l >> r;

        int u_b = lower_bound(r+1, vec);
        int l_b = lower_bound(l, vec);

        cout << u_b - l_b << " ";
    }

    return 0;
}
