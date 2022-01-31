#include <iostream>

using namespace std;

class Point {
public:
    int x, y;
    Point(int x, int y): x(x), y(y) {}
};

int area(Point a, Point b, Point c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

bool intersect_1(int a, int b, int c, int d) {
    if (a > b)
        swap(a, b);
    if (c > d)
        swap(d, c);
    return max(a, c) <= min(b, d);
}

bool intersect_2(Point a, Point b, Point c, Point d) {
    bool flag1 = intersect_1(a.x, b.x, c.x, d.x);
    bool flag2 = intersect_1(a.y, b.y, c.y, d.y);
    bool flag3 = area(a, b, c) * area(a, b, d) <= 0;
    bool flag4 = area(c, d, a) * area(c, d, b) <= 0;

    return flag1 & flag2 & flag3 & flag4;
}

int main() {
    int ax, ay, bx, by;
    int cx, cy, dx, dy;

    cin >> ax >> ay >> bx >> by;
    cin >> cx >> cy >> dx >> dy;

    Point a_p(ax, ay), b_p(bx, by);
    Point c_p(cx, cy), d_p(dx, dy);

    bool ans = intersect_2(a_p, b_p, c_p, d_p);
    if (ans)
        cout << "YES";
    else
        cout << "NO";
    return 0;
}
