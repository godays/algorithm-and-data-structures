#include <iostream>
#include <vector>
#include <set>

using namespace std;

vector<vector<int>> graph;
vector<int> used, enter, ret;
set<int> artPoints;
int time, n, m;


void dfs(int v, int parent = -1) {
    used[v] = 1;
    enter[v] = ret[v] = time++;
    int child = 0;
    for (int i = 0; i < graph[v].size(); ++i) {
        int to = graph[v][i];
        if (to == parent)
            continue;
        if (used[to]) {
            ret[v] = min(ret[v], enter[to]);
        } else {
            dfs(to, v);
            child++;
            ret[v] = min(ret[v], ret[to]);
            if ((ret[to] >= enter[v]) && (parent != -1))
                artPoints.insert(v);
        }
    }
    if ((parent == -1) && (child > 1))
        artPoints.insert(v);
}

void findAll() {
    time = 1;
    for (int i = 1; i <= n; ++i) {
        if (!used[i]) dfs(i);
    }
}

int main() {
    cin >> n >> m;

    graph.resize(n + 1);
    used.resize(n + 1);
    enter.resize(n + 1);
    ret.resize(n + 1);

    for (int i = 0; i < m; i++) {
        int begin, end;
        cin >> begin >> end;
        graph[begin].push_back(end);
        graph[end].push_back(begin);
    }

    findAll();

    cout << artPoints.size() << '\n';

    for (int artPoint: artPoints) {
        cout << artPoint << ' ';
    }

    return 0;
}