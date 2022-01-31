#include <iostream>
#include <vector>

using namespace std;

vector<int> merge(vector<int> left_array, vector<int> right_array) {
    int n = left_array.size();
    int m = right_array.size();
    int i = 0;
    int j = 0;
    vector<int> result_array(n + m);

    while (i + j < n + m) {
        if (j == m || (i < n && left_array[i] < right_array[j])) {
            result_array[i + j] = left_array[i];
            i++;
        }
        else {
            result_array[i + j] = right_array[j];
            j++;
        }
    }

    return result_array;
}

vector<int> merge_sort(vector<int> array) {
    int n = array.size();

    if (n == 1)
        return array;

    vector<int> left_array;
    vector<int> right_array;
    copy(array.begin(), array.begin() + n / 2, back_inserter(left_array));
    copy(array.begin() + n / 2, array.end(), back_inserter(right_array));

    left_array = merge_sort(left_array);
    right_array = merge_sort(right_array);

    return merge(left_array, right_array);
}

int main() {
    int n;
    cin >> n;
    vector<int> array(n);

    for (int i = 0; i < n; i++)
        cin >> array[i];

    array = merge_sort(array);

    for (int i = 0; i < n; i++)
        cout << array[i] << " ";

    return 0;
}