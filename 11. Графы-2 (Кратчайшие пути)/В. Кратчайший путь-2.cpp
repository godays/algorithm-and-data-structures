#include <iostream>
#include <vector>
#include <set>


int n, m;
int const INF = 400000;


using namespace std;


vector<int> dijkstra(vector<vector<pair<int, int>>>& graph) {
    vector<int> dist(n, INF);
    int start = 0;
    dist[start] = 0;
    set<pair<int, int>> queue;
    queue.insert({0, start});

    while (!queue.empty()) {
        pair<int, int> top = *queue.begin();
        int u = top.second;
        queue.erase(top);

        for (pair<int, int> next: graph[u]) {
            int v = next.first;
            int len = next.second;
            if (dist[v] > dist[u] + len) {
                if (queue.find({dist[v], v}) != queue.end())
                    queue.erase(queue.find({dist[v], v}));
                dist[v] = dist[u] + len;
                queue.insert({dist[v], v});
            }
        }
    }
    return dist;
}

int main() {
    cin >> n >> m;
    vector<vector<pair<int, int>>> graph(n, vector<pair<int, int>>());

    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u-1].push_back({v-1, w});
        graph[v-1].push_back({u-1, w});
    }

    vector<int> res = dijkstra(graph);
    for (int i: res)
        cout << i << " ";
    return 0;
}
