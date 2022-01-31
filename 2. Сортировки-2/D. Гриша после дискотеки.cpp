#include <iostream>
#include <vector>

using namespace std;

const int MAX_A = 'a';
const int ALPHABET_LENGTH = 26;

bool if_anagram(int r_index, vector<char> source, vector<int>& cnt) {
    if (cnt[source[r_index] - MAX_A]) {
        cnt[source[r_index] - MAX_A]--;
        return true;
    }
    return false;
}

int main() {
    int n, m;
    long long res = 0;
    cin >> n >> m;
    vector<char> source(n);
    vector<char> cards(m);
    vector<int> cnt(ALPHABET_LENGTH);

    for (int i = 0; i < n; i++)
        cin >> source[i];
    for (int i = 0; i < m; i++) {
        cin >> cards[i];
        cnt[cards[i] - MAX_A]++;
    }

    int l_index = 0;
    int r_index = 0;
    long long tmp_counter = 0;
    vector<int> cur_cnt = cnt;

    while (r_index < n)
        if (cnt[source[r_index] - MAX_A] == 0) {
            res += (1 + tmp_counter) * tmp_counter / 2;
            l_index = r_index + 1;
            r_index++;
            tmp_counter = 0;
            cur_cnt = cnt;

        } else if (if_anagram(r_index, source, cur_cnt)) {
            tmp_counter++;
            r_index++;

        } else {
            res += tmp_counter;
            cur_cnt[source[l_index] - MAX_A]++;
            l_index++;
            tmp_counter--;
        }

    cout << res + tmp_counter * (tmp_counter + 1) / 2;
    return 0;
}