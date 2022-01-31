#include <iostream>
#include <vector>

using namespace std;

bool can_produce(int time, int n, int x, int y) {
    time -= x;
    return (time / x + time / y) + 1 >= n;
}

int main() {
    int n, x, y;
    cin >> n >> x >> y;
    if (x > y)
        swap(x, y);

    int l = x - 1;
    int r = n * y + 1;

    while (l < r - 1) {
        int m = (l + r) / 2;
        if (can_produce(m, n, x, y))
            r = m;
        else
            l = m;
    }

    cout << r;
    return 0;
}
