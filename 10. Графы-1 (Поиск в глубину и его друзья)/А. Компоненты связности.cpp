#include <iostream>
#include <vector>

using namespace std;

vector<char> color;
vector<int> ans;
vector<vector<int>> graph;
int cnt = 0;

void dfs(int v) {
    ans[v] = cnt;
    color[v] = 1;
    for (int &i: graph[v])
        if (color[i] == 0) {
            dfs(i);
        }
    color[v] = 2;
}

int main() {
    int n, m;
    cin >> n >> m;
    color.assign(n, 0);
    ans.assign(n, 0);
    graph.assign(n, vector<int>());

    for (int i = 0; i < m; i++) {
        int v1, v2;
        cin >> v1 >> v2;
        v1--;
        v2--;
        graph[v1].push_back(v2);
        graph[v2].push_back(v1);
    }


    for (int i = 0; i < n; i++) {
        if (color[i] == 0) {
            cnt++;
            dfs(i);
        }
    }

    cout << cnt << '\n';

    for (int i = 0; i < n; i++)
        cout << ans[i] << " ";
    return 0;
}
