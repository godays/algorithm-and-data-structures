#include <iostream>
#include <vector>

using namespace std;

int const INF = 2e9;
int n, m;
int s, t;
vector<int> used;

struct Edge {
    int from_v, to_v, cap, dist, flow;

    Edge(int u, int v, int cap, int dist, int flow = 0) {
        this->from_v = u;
        this->to_v = v;
        this->cap = cap;
        this->dist = dist;
        this->flow = flow;
    }
};

vector<vector<Edge>> graph;

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

void restore(vector<int>& path, int u, int v) {
    path.push_back(u + 1);
    if (u == v)
        return;

    for (auto &edge: graph[u]) {
        if (edge.flow == edge.cap && edge.cap != 0) {
            edge.flow = 0;
            graph[edge.to_v][edge.dist].flow = 0;
            restore(path, edge.to_v, v);
            break;
        }
    }
}

int main() {
    cin >> n >> m >> s >> t;

    graph.assign(n, vector<Edge>());

    for (int i = 0; i < m; ++i) {
        int ai, bi, ci;
        cin >> ai >> bi;
        ai--;
        bi--;

        graph[ai].push_back({ai, bi, 1, (int) graph[bi].size()});
        graph[bi].push_back({bi, ai, 0, (int) graph[ai].size() - 1});
    }

    int ans = 0;
    s --;
    t--;

    while (true) {
        used.assign(n, 0);

        int delta = pushFlow(s, t, INF);
        if (delta > 0)
            ans += delta;
        else
            break;
    }

    if (ans < 2)
        cout << "NO";
    else {
        vector<int> ans_1;
        vector<int> ans_2;
        restore(ans_1, s, t);
        restore(ans_2, s, t);
        if (ans_1.size() > ans_2.size())
            swap(ans_1, ans_2);

        cout << "YES\n";
        for (auto i: ans_1)
            cout << i << " ";
        cout << '\n';
        for (auto i: ans_2)
            cout << i << " ";
    }
    return 0;
}
