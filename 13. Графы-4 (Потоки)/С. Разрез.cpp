#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int const INF = 2e9;
int n, m;
int s, t;
vector<int> used;

struct Edge {
    int from_v, to_v, cap, dist, flow;
};

vector<vector<Edge>> graph;
vector<Edge> edge_order;
vector<int> cut_edges;
int total_caps;

int pushFlow(int v, int to, int curFlow) {
    used[v] = 1;
    if (v == to)
        return curFlow;
    for (auto &edge: graph[v]) {
        int u = edge.to_v;
        if (!used[u] && edge.flow < edge.cap) {
            int nextFlow = min(curFlow, edge.cap - edge.flow);
            int delta = pushFlow(u, to, nextFlow);
            if (delta > 0) {
                edge.flow += delta;
                graph[u][edge.dist].flow -= delta;
                return delta;
            }
        }
    }
    return 0;
}

bool bfs() {
    vector<int> d(n, -1);
    queue<int> q;
    d[s] = 0;
    q.push(s);

    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (auto &edge: graph[v]) {
            int u = edge.to_v;
            if (edge.flow < edge.cap && d[u] == -1) {
                d[u] = d[v] + 1;
                q.push(u);
            }
        }
    }
    return d[t] != -1;
}

void change(vector<bool> &b_to_s, int v) {
    if (b_to_s[v])
        return;
    b_to_s[v] = true;
    for (auto &edge: graph[v]) {
        if (edge.flow != edge.cap)
            change(b_to_s, edge.to_v);
    }
}

void restore() {
    vector<bool> b_to_s(n, false);
    change(b_to_s, s);
    int i = 0;
    for (auto &edge: edge_order) {
        int u = edge.from_v;
        int v = edge.to_v;
        i++;
        if (b_to_s[u] == b_to_s[v])
            continue;
        cut_edges.push_back(i);
        total_caps += edge.cap;
    }
}

int main() {
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
        edge_order.push_back(graph[ai].back());
    }


    while (bfs()) {
        used.assign(n, 0);
        pushFlow(s, t, INF);
    }

    restore();
    cout << cut_edges.size() << " " << total_caps << '\n';
    for (auto i: cut_edges)
        cout << i << " ";

    return 0;
}
