#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n, m;
vector<vector<int>> graph;
vector<int> ans;
vector<int> color;
bool hasCycle = false;

void dfs(int v) {
    if (hasCycle)
        return;

    color[v] = 1;

    for (int to: graph[v]) {
        if (!color[to])
            dfs(to);
        else if (color[to] == 1) {
            hasCycle = true;
        }
    }
    color[v] = 2;
    ans.push_back(v);
}

void topSort() {
    ans.clear();
    for (int i = 0; i < n; ++i)
        if (!color[i])
            dfs(i);
    reverse(ans.begin(), ans.end());
}

int main() {
    cin >> n >> m;
    color.assign(n, 0);
    graph.assign(n, vector<int>());

    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        graph[a].push_back(b);
    }

    color.assign(n, 0);
    topSort();

    if (hasCycle)
        cout << -1;
    else
        for (int i: ans)
            cout << i + 1 << " ";
    return 0;
}
