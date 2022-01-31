#include <iostream>
#include <vector>

int main() {
    int n;
    std::cin >> n;
    std::vector<int> array(n);

    for (int i = 0; i < n; i++)
        std::cin >> array[i];

    for (int i = 1; i < n; i++) {
        int j = i;
        while (j > 0 & array[j - 1] > array[j]) {
            std::swap(array[j - 1], array[j]);
            j--;
        }
    }

    for (int i = 0; i < n; i++)
        std::cout << array[i] << " ";

    return 0;
}