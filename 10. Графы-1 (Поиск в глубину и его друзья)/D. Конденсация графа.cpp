#include <iostream>
#include <vector>
#include <map>
#include <set>


using namespace std;

vector<vector<int>> graph, reverse_graph;
vector<int> order, numberOfComponent;
vector<bool> used;
set<pair<int, int>> cond_edges;
int n, m, col;

void dfs_for_graph(int v) {
    used[v] = true;
    for (int to : graph[v]) {
        if (!used[to])
            dfs_for_graph(to);
    }
    order.push_back(v);
}

void dfs_for_rev_graph(int v) {
    used[v] = true;
    numberOfComponent[v] = col;
    for (int to : reverse_graph[v]) {
        if (!used[to])
            dfs_for_rev_graph(to);
    }
}

int main() {
    cin >> n >> m;

    graph.resize(n);
    reverse_graph.resize(n);
    used.resize(n);
    numberOfComponent.resize(n);

    for (int i = 0; i < m; ++i) {
        int begin, end;
        cin >> begin >> end;
        begin--;
        end--;
        graph[begin].push_back(end);
        reverse_graph[end].push_back(begin);
    }

    used.assign(n, false);
    for (int i = 0; i < n; ++i) {
        if (!used[i]) {
            dfs_for_graph(i);
        }
    }

    used.assign(n, false);
    col = 1;
    for (int i = 0; i < n; ++i) {
        int v = order[n - 1 - i];
        if (!used[v]) {
            dfs_for_rev_graph(v);
            col++;
        }
    }


    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < graph[i].size(); j++) {
            int to = graph[i][j];
            if (numberOfComponent[i] != numberOfComponent[to])
                cond_edges.insert(make_pair(numberOfComponent[i], numberOfComponent[to]));
        }
    }


    cout << cond_edges.size();
    return 0;
}