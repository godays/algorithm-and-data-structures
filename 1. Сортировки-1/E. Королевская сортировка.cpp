#include <iostream>

#include <map>
#include <string>
#include <vector>

using namespace std;

bool cmp(pair<string, int> left, pair<string, int> right) {
    if (left.first < right.first)
        return true;
    else if (left.first == right.first) {
        return left.second < right.second;
    }
    return false;
}

int split(int l_ind, int r_ind, pair<string, int> pivot, vector<pair<string, int> >& vec) {
    int i = l_ind;
    int j = r_ind;
    while (i <= j) {
        while (cmp(vec[i], pivot))
            i++;
        while (cmp(pivot, vec[j]))
            j--;
        if (i >= j)
            break;
        swap(vec[i++], vec[j--]);
    }
    return j;
}

void qsort(int l_ind, int r_ind, vector<pair<string, int> >& vec) {
    if (r_ind <= l_ind)
        return;

    int ind = (rand() % (r_ind - l_ind)) + l_ind;
    pair<string, int> pivot = vec[ind];
    int m = split(l_ind, r_ind, pivot, vec);
    qsort(l_ind, m, vec);
    qsort(m + 1, r_ind, vec);
}

int roman_to_int(string num) {
    map<char, int> ROMAN = { { 'L', 50 }, { 'X', 10 }, { 'V', 5 }, { 'I', 1 } };

    int res = 0;
    for (int i = 0; i < num.size() - 1; i++) {
        if (ROMAN[num[i]] < ROMAN[num[i + 1]])
            res -= ROMAN[num[i]];
        else
            res += ROMAN[num[i]];
    }

    res += ROMAN[num[num.size() - 1]];
    return res;
}

int main() {
    int n;
    cin >> n;
    vector<pair<string, int> > kings;
    map<int, string> int_to_roman;
    string name, num_name_str;

    for (int i = 0; i < n; i++) {
        cin >> name >> num_name_str;
        int num_name = roman_to_int(num_name_str);
        int_to_roman[num_name] = num_name_str;
        kings.push_back(make_pair(name, num_name));
    }
    qsort(0, n - 1, kings);

    for (const auto& it : kings) {
        cout << it.first << " " << int_to_roman[it.second] << "\n";
    }
    return 0;
}
