#include <iostream>
#include <vector>

int const pow_16 = 1 << 16;
int const pow_30 = 1 << 30;

using namespace std;

int main() {
    int n, x, y, a_0;
    int m, z, t, b_0;

    cin >> n >> x >> y >> a_0;
    cin >> m >> z >> t >> b_0;

    if (m == 0) {
        cout << "0";
        return 0;
    }

    vector<long long> sum_a(n);
    vector<unsigned> c(2 * m);
    a_0 %= pow_16;
    b_0 %= pow_30;

    long long prev_a = a_0;
    long long cur_a = a_0;
    unsigned long long prev_b = b_0;
    unsigned long long cur_b = b_0;

    sum_a[0] = cur_a;
    c[0] = cur_b % n;

    for (int i = 1; i < n; i++) {
        cur_a = (x * prev_a + y) % pow_16;
        sum_a[i] = sum_a[i - 1] + cur_a;
        prev_a = cur_a;
    }

    for (int i = 1; i < 2 * m; i++) {
        cur_b = (unsigned long long)(z * prev_b + t) % pow_30;
        c[i] = cur_b % n;
        prev_b = cur_b;
    }


    long long res = 0;

    for (int k = 0; k < m; k++) {
        int l = min(c[2 * k], c[2 * k + 1]);
        int r = max(c[2 * k], c[2 * k + 1]);

        if (l == 0)
            res += sum_a[r];
        else
            res += sum_a[r] - sum_a[l - 1];
    }

    cout << res;
    return 0;
}
