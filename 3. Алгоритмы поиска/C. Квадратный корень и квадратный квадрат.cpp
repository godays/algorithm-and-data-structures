#include <iostream>
#include <cmath>

using namespace std;

const double EPS = 1e-6;
double C;
int ITN;

double fun(double x) {
    return pow(x, 2) + sqrt(x) - C;
}

int main() {
    double l = 0;
    cin >> C;
    double r = C;
    ITN = (int)log2((r - l) / EPS);

    for (int i = 0; i <= ITN; i++) {
        double m = (l + r) / 2;
        if (fun(m) < 0)
            l = m;
        else
            r = m;
    }

    cout.precision(7);
    cout << r;
    return 0;
}
