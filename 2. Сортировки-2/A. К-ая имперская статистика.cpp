#include <iostream>
#include <vector>

using namespace std;

int split(int l_ind, int r_ind, int pivot, vector<int>& vec) {
    int m = l_ind;
    for (int i = l_ind; i < r_ind; i++)
        if (vec[i] < pivot) {
            swap(vec[i], vec[m]);
            m++;
        }
    return m;
}

int find(int k, int l_ind, int r_ind, vector<int>& vec) {
    if (r_ind - l_ind == 1)
        return vec[k];

    int ind = (rand() % (r_ind - l_ind)) + l_ind;
    int pivot = vec[ind];
    int m = split(l_ind, r_ind, pivot, vec);

    if (k < m)
        return find(k, l_ind, m, vec);
    else
        return find(k, m, r_ind, vec);


}


int main() {
    int n;
    int m;

    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    cin >> m;

    for (int iter = 0; iter < m; iter++) {
        vector<int> arr_copy = arr;
        int i, j, k;
        cin >> i >> j >> k;
        cout << find(k - 1 + i - 1, i - 1, j, arr_copy) << endl;
    }

    return 0;
}
