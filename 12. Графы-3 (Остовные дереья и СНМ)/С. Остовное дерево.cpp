#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int n;
vector<pair<int, int>> points;
vector<bool> used;
vector<int> selEdge;
vector<double> minEdge;

int const INF = 1e9;

double dist(int v, int to) {
    if (v == to)
        return INF;
    pair<int, int> a = points[v];
    pair<int, int> b = points[to];

    return sqrt((b.first - a.first) * (b.first - a.first) + (b.second - a.second) * (b.second - a.second));
}

int main() {
    cin >> n;
    used.resize(n);
    points.resize(n);
    selEdge.assign(n, -1);
    minEdge.assign(n, INF);

    minEdge[0] = 0;

    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        points[i] = {x, y};
    }

    double res = 0;
    for (int i = 0; i < n; i++) {
        int v = -1;
        for (int j = 0; j < n; j++)
            if (!used[j] && (v == -1 || minEdge[j] < minEdge[v]))
                v = j;
        used[v] = true;
        if (selEdge[v] != -1)
            res += dist(v, selEdge[v]);

        for (int to = 0; to < n; ++to) {
            double d = dist(v, to);
            if (d < minEdge[to]) {
                minEdge[to] = d;
                selEdge[to] = v;
            }
        }
    }

    cout << res;

    return 0;
}
