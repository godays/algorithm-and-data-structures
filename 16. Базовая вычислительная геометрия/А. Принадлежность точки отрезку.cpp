#include <iostream>

using namespace std;

class Point {
public:
    int x, y;
    Point(int x, int y): x(x), y(y) {}
};

class Vector {
public:
    int x, y;
    Vector(Point p1, Point p2) {
        x = p2.x - p1.x;
        y = p2.y - p1.y;
    }
};

int dot(Vector v1, Vector v2) {
    return v1.x * v2.x + v1.y * v2.y;
}

int cross(Vector v1, Vector v2) {
    return v1.x * v2.y - v1.y * v2.x;
}

int main() {
    int cx, cy, ax, ay, bx, by;
    cin >> cx >> cy >> ax >> ay >> bx >> by;

    Point a_p(ax, ay), b_p(bx, by), c_p(cx, cy);
    Vector ab(a_p, b_p), ba(b_p, a_p), ac(a_p, c_p), bc(b_p, c_p);

    int cp_ab_ac = cross(ab, ac);
    int dp_ab_ac = dot(ab, ac);
    int dp_ba_bc = dot(ba, bc);

    if (cp_ab_ac == 0 & dp_ab_ac >= 0 & dp_ba_bc >= 0)
        cout << "YES";
    else
        cout << "NO";
    return 0;
}
