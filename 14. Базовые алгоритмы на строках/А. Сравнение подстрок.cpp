#include <iostream>
#include <vector>
#include <string>

using namespace std;

long long const PRIME = 61;
long long const MOD = 1e9 + 17;
vector<long long> pows;
vector<long long> hashes;

long long getHash(long long l, long long r) {
    if (l == 0)
        return hashes[r];
    return ((hashes[r] - hashes[l - 1] * pows[r - l + 1]) % MOD + MOD) % MOD;
}

int main() {
    int m;
    string str;

    cin >> str >> m;

    hashes.assign(str.length() + 1, 0);
    pows.assign(str.length() + 1, 1);

    hashes[0] = str[0] - 'a' + 1;

    for (int i = 1; i < str.length(); ++i) {
        hashes[i] = (hashes[i - 1] * PRIME + str[i] - 'a' + 1) % MOD;
        pows[i] = (pows[i - 1] * PRIME) % MOD;
    }

    for (int i = 0; i < m; ++i) {
        long long a, b, c, d;
        cin >> a >> b >> c >> d;
        a--;
        b--;
        c--;
        d--;
        cout << (getHash(a, b) == getHash(c, d) ? "Yes\n" : "No\n");
    }
    return 0;
}
