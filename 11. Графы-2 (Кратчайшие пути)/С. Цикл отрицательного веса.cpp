#include <iostream>
#include <vector>
#include <set>

using namespace std;


int const NO_EDGE = 100000;
int const INF = 1e9;
int n;

vector<vector<int>> dist;
vector<vector<int>> nxt;
int start = -1;

void floyd() {
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++)
                if (dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    nxt[i][j] = nxt[i][k];
                }
        }
        for (int u = 0; u < n; u++) {
            if (dist[u][u] < 0) {
                start = u;
                break;
            }
        }
        if (start >= 0)
            break;
    }
}


int main() {
    cin >> n;

    dist.assign(n, vector<int>(n, INF));
    nxt.assign(n, vector<int>(n, 0));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            nxt[i][j] = j;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int w;
            cin >> w;
            if (w != NO_EDGE)
                dist[i][j] = w;
        }
    }

    floyd();

    if (start < 0) {
        cout << "NO";
    } else {
        int u = start;
        vector<int> ans;
        set<int> ans_set;

        while (ans_set.find(u) == ans_set.end()) {
            ans.push_back(u + 1);
            ans_set.insert(u);
            u = nxt[u][start];
        }

        cout << "YES\n" << ans.size() << "\n";
        for (int el: ans)
            cout << el << " ";
    }
    return 0;
}