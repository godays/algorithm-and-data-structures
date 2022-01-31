#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

class Point {
public:
    int x, y;

    Point(int x, int y) : x(x), y(y) {}
};

int cross(Point p1, Point p2) {
    return p1.x * p2.y - p2.x * p1.y;
}

int main() {
    int n;
    vector<Point> points;
    cin >> n;

    for (int i = 0; i < n; ++i) {
        int x, y;
        cin >> x >> y;
        points.push_back(Point(x, y));
    }

    int ans = 0;

    for (int i = 0; i < n; ++i)
        ans += cross(points[i], points[(i + 1) % n]);

    cout << abs(ans) / 2.0;
    return 0;
}
