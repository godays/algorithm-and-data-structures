#include <iostream>
#include <vector>

using namespace std;

int const INF = 2e9;
vector<int> used;

struct Edge {
    int from_v, to_v, cap, dist, flow;
};

vector<vector<Edge>> graph;

int pushFlow(int v, int t, int curFlow) {
    used[v] = 1;
    if (v == t)
        return curFlow;
    for (auto &edge: graph[v]) {
        int u = edge.to_v;
        if (!used[u] && edge.flow < edge.cap) {
            int nextFlow = min(curFlow, edge.cap - edge.flow);
            int delta = pushFlow(u, t, nextFlow);
            if (delta > 0) {
                edge.flow += delta;
                graph[u][edge.dist].flow -= delta;
                return delta;
            }
        }
    }
    return 0;
}

int main() {
    int n, m;
    int s, t;
    cin >> n >> m;

    graph.assign(n, vector<Edge>());
    s = 0;
    t = n - 1;

    for (int i = 0; i < m; ++i) {
        int ai, bi, ci;
        cin >> ai >> bi >> ci;
        ai--;
        bi--;

        graph[ai].push_back({ai, bi, ci, (int) graph[bi].size(), 0});
        graph[bi].push_back({bi, ai, ci, (int) graph[ai].size() - 1, 0});
    }

    int ans = 0;

    while (true) {
        used.assign(n, 0);
        int delta = pushFlow(s, t, INF);
        if (delta > 0)
            ans += delta;
        else
            break;
    }

    cout << ans;
    return 0;
}
