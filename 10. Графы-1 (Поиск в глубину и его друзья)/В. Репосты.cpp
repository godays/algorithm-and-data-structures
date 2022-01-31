#include <iostream>
#include <vector>
#include <cctype>
#include <string>
#include <unordered_map>
#include <algorithm>

using namespace std;

string lower_str(string str) {
    transform(str.begin(), str.end(), str.begin(),
              [](unsigned char c) { return std::tolower(c); });
    return str;
}

vector<int> path_len;
vector<vector<int>> graph;
vector<bool> used;

void dfs(int v) {
    used[v] = true;

    for (int i: graph[v]) {
        if (!used[i])
            dfs(i);
        path_len[v] = max(path_len[v], 1 + path_len[i]);
    }

}

int main() {
    int n;
    cin >> n;
    n++;
    int name_cnt = 0;
    path_len.assign(n, 0);
    used.assign(n, false);
    unordered_map<string, int> coded_names;
    graph.assign(n, vector<int>());

    for (int i = 0; i < n - 1; ++i) {
        string name1, reposted, name2;
        cin >> name1 >> reposted >> name2;
        name1 = lower_str(name1);
        name2 = lower_str(name2);
        if (coded_names.find(name2) == coded_names.end()) {
            coded_names[name2] = name_cnt;
            name_cnt++;
        }
        if (coded_names.find(name1) == coded_names.end()) {
            coded_names[name1] = name_cnt;
            name_cnt++;
        }
        graph[coded_names[name2]].push_back(coded_names[name1]);
    }

    dfs(0);

    cout << path_len[0] + 1;
    return 0;
}
