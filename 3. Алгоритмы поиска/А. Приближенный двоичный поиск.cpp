#include <iostream>
#include <vector>

using namespace std;

int lower_bound(const long long& x, const vector<long long>& vec) {
    int l = 0;
    int r = vec.size();

    while (l < r) {
        int mid = l + (r - l) / 2;

        if (x <= vec[mid])
            r = mid;
        else
            l = mid + 1;
    }
    return l;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m;
    cin >> n >> m;
    vector<long long> vec(n);

    for (int i = 0; i < n; i++)
        cin >> vec[i];

    for (int i = 0; i < m; i++) {
        long long curr_num;
        cin >> curr_num;

        int l_b = lower_bound(curr_num, vec);
        int r_b = lower_bound(curr_num + 1, vec);

        if (l_b == r_b)
            l_b = (l_b - 1) * (l_b > 0);

        if (l_b == n) {
            l_b = n - 1;
            r_b = n - 1;
        }

        if (abs(vec[l_b] - curr_num) <= abs(vec[r_b] - curr_num))
            cout << vec[l_b] << "\n";
        else
            cout << vec[r_b] << "\n";
    }

    return 0;
}