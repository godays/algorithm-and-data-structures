#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

const double EPS = 1e-6;
const double ITN = log((1 - 0) / EPS) * log(3.0 / 2) + 100;
int v_p, v_f;
double a;

double time_needed(double x0) {
    return sqrt(pow(0 - x0, 2) + pow(1 - a, 2)) / v_p
           + sqrt(pow(1 - x0, 2) + pow(0 - a, 2)) / v_f;
}

int main() {
    cin >> v_p >> v_f >> a;
    double l = 0.0;
    double r = 1.0;

    for (int i = 0; i <= ITN; i++) {
        double m1 = l + (r - l) / 3;
        double m2 = l + 2 * (r - l) / 3;

        if (time_needed(m1) < time_needed(m2))
            r = m2;
        else
            l = m1;
    }

    cout << fixed << setprecision(4) << r;
    return 0;
}
