#include <iostream>
#include <vector>

using namespace std;

const int M = 101;

int main() {
    vector<int> cnt(M);
    vector<int> array;
    int num;

    while (cin >> num)
        array.push_back(num);

    for (const int& i : array)
        cnt[i]++;

    int i = 0;
    for (int j = 0; j < M; j++) {
        while (cnt[j] > 0) {
            array[i++] = j;
            cnt[j]--;
        }
    }

    for (const int& it: array)
        cout << it << " ";
    return 0;
}
