#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int MIN_A = 'a';
const int ARRAY_MAX_SIZE = 26;

void count_sort(vector<int> &p, vector<string> table, int m, int k) {
    vector<int> cnt(ARRAY_MAX_SIZE);
    vector<vector<int>> strings_with_dig(ARRAY_MAX_SIZE);

    for (const int &i: p) {
        int index = table[i][m - 1 - k] - MIN_A;
        cnt[index]++;
        strings_with_dig[index].push_back(i);
    }

    int i = 0;
    for (int j = 0; j < ARRAY_MAX_SIZE; j++) {
        int ind_vec_it = 0;
        while (cnt[j] > 0) {
            p[i++] = strings_with_dig[j][ind_vec_it++];
            cnt[j]--;
        }
    }
}

int main() {
    int n;
    int m;
    int k;
    string curr_num;
    cin >> n >> m >> k;
    vector<int> p(n);
    vector<string> table(n);

    for (int i = 0; i < n; i++) {
        cin >> curr_num;
        p[i] = i;
        table[i] = curr_num;
    }

    for (int i = 0; i < k; i++)
        count_sort(p, table, m, i);

    for (const int &i: p) {
        cout << table[i] << endl;
    }
    return 0;
}
