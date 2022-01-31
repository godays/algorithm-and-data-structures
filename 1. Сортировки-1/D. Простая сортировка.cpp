#include <iostream>
#include <vector>

using namespace std;

int split(int l_ind, int r_ind, int pivot, vector<int>& vec) {
    int i = l_ind;
    int j = r_ind;
    while (i <= j) {
        while (vec[i] < pivot)
            i++;
        while (vec[j] > pivot)
            j--;
        if (i >= j)
            break;
        swap(vec[i++], vec[j--]);
    }
    return j;
}

void qsort(int l_ind, int r_ind, vector<int>& vec) {
    if (r_ind <= l_ind)
        return;

    int ind = (rand() % (r_ind - l_ind)) + l_ind;
    int pivot = vec[ind];
    int m = split(l_ind, r_ind, pivot, vec);
    qsort(l_ind, m, vec);
    qsort(m + 1, r_ind, vec);
}

int main() {
    int n;
    cin >> n;
    vector<int> vec(n);

    for (int i = 0; i < n; i++)
        cin >> vec[i];

    qsort(0, n - 1, vec);

    for (const int& it : vec)
        cout << it << " ";
    return 0;
}