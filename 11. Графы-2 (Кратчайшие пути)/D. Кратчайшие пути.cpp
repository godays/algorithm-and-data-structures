#include <iostream>
#include <vector>

using namespace std;

long long const INF = (long long) 1e20;
int n, m, s;

struct edge {
    int u;
    int v;
    long long w;

    edge(int u, int v, long long w): u(u), v(v), w(w) {}
};

vector<edge> edges;
vector<vector<int>> graph;
vector<int> used;
vector<long long> dist;

void findShortestWays() {
    dist[s] = 0;

    for (int i = 0; i < n; i++)
        for (auto & edge : edges) {
            int u = edge.u;
            int v = edge.v;
            long long w = edge.w;

            if ((dist[u] < INF) && (dist[v] > dist[u] + w))
                dist[v] = max(-INF, dist[u] + w);
        }
}

void dfs(int v) {
    used[v] = 1;
    for (int to : graph[v])
        if (!used[to])
            dfs(to);
}


int main() {
    cin >> n >> m >> s;
    s--;

    dist.assign(n, INF);
    graph.resize(n);
    used.assign(n, 0);

    for (int i = 0; i < m; i++) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        u--;
        v--;
        graph[u].push_back(v);
        edges.emplace_back(u, v, w);
    }

    findShortestWays();


    for (int i = 0; i < n; i++)
        for (auto & edge : edges) {
            int u = edge.u;
            int v = edge.v;
            long long w = edge.w;
            if ((dist[u] < INF) && (dist[v] > dist[u] + w) && !used[v])
                dfs(v);
        }

    for (int i = 0; i < n; i++) {
        if (dist[i] == INF)
            cout << "*\n";
        else if (used[i])
            cout << "-\n";
        else
            cout << dist[i] << '\n';
    }
    return 0;
}
