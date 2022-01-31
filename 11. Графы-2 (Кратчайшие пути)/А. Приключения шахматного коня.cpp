#include <iostream>
#include <deque>
#include <map>
#include <vector>
#include <utility>

using namespace std;

int const POS_CNT = 4;

class Field {
public:
    Field(int n) {
        fill_graph(n);
    }

    void bfs(pair<int, int> start, map<pair<int, int>, int>& distance, map<pair<int, int>, pair<int, int>>& parents) {
        distance[start] = 0;
        deque<pair<int, int>> q;
        q.push_front(start);

        while (!q.empty()) {
            pair<int, int> cur_v = q.front();
            q.pop_front();
            for (auto neight_v: graph[cur_v]) {
                if (distance.find(neight_v) == distance.end()) {
                    distance[neight_v] = distance[cur_v] + 1;
                    parents[neight_v] = cur_v;
                    q.push_back(neight_v);
                }
            }
        }
    }

    void fill_graph(int n) {
        int i, j, x1, x2, y1, y2, k;
        int dx[8]{ 2, -2, 1, -1, 3, -1, 2, 0 };
        int dy[8]{ 1, 1, 2, 2, 2, 2, 3, 3 };

        for (i = 0; i < n; i++) {
            for (j = 0; j < n; j++) {
                x1 = i + 1;
                y1 = j + 1;
                for (k = 0; k < POS_CNT; k++) {
                    if (i + dx[k] >= 0 && j + dy[k] < n) {
                        x2 = i + dx[POS_CNT + k];
                        y2 = j + dy[POS_CNT + k];
                        graph[make_pair(x1, y1)].push_back(make_pair(x2, y2));
                        graph[make_pair(x2, y2)].push_back(make_pair(x1, y1));
                    }
                }
            }
        }
    }

    map<pair<int, int>, vector<pair<int, int>>> graph;
};


int main() {
    int n;
    cin >> n;
    pair<int, int> st;
    pair<int, int> end;
    cin >> st.first >> st.second;
    cin >> end.first >> end.second;

    Field g(n);
    map<pair<int, int>, int> distance;
    map<pair<int, int>, pair<int, int>> parents;
    g.bfs(st, distance, parents);

    vector<pair<int, int>> path;
    pair<int, int> parent = parents[end];
    path.push_back(end);

    while (true) {
        path.push_back(parent);
        if (parents.find(parent) == parents.end())
            break;
        parent = parents[parent];
    }
    cout << path.size() << '\n';

    for (int i = path.size() - 1; i >=0; i--) {
        cout << path[i].first << " " << path[i].second << '\n';
    }

    return 0;
}
