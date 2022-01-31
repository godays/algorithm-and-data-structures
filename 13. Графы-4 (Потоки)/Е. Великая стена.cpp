#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int const INF = 1e9;
int const MAX_SIZE = 1e5;

struct Edge {
    int to, reverse_edge, capacity, flow, x, y;

    Edge(int to, int capacity, int reverse_edge = -1, int x = -1, int y = -1) {
        this->to = to;
        this->reverse_edge = reverse_edge;
        this->capacity = capacity;
        this->flow = 0;
        this->x = x;
        this->y = y;
    }
};

struct Node {
    int depth = INF;
    int first_save_edge = 0;
    vector<Edge> edges;
};

class FlowNetwork {
public:
    FlowNetwork(int size = 0) {
        nodes = vector<Node>(size);
        source_idx = 0;
        sink_idx = 0;
    }

    void add_edge(int from_v, int to_v, int cap) {
        int reverse_edge_idx_to = (nodes[from_v].edges).size();
        int reverse_edge_idx_from = (nodes[to_v].edges).size();
        nodes[from_v].edges.emplace_back(to_v, cap, reverse_edge_idx_from);
        nodes[to_v].edges.emplace_back(from_v, 0, reverse_edge_idx_to);
    }

    void add_direct_edge(int from_v, int to_v, int cap, int x, int y) {
        nodes[from_v].edges.emplace_back(to_v, cap, -1, x, y);
    }

    bool bfs_from_source() {
        for (auto &node: nodes) {
            node.depth = INF;
            node.first_save_edge = 0;
        }

        nodes[source_idx].depth = 0;
        queue<int> q;
        q.push(source_idx);

        while (!q.empty()) {
            int vertex = q.front();
            q.pop();
            for (auto &edge: nodes[vertex].edges) {
                if (edge.flow < edge.capacity && nodes[edge.to].depth == INF) {
                    nodes[edge.to].depth = nodes[vertex].depth + 1;
                    q.push(edge.to);
                }
            }
        }
        return nodes[sink_idx].depth != INF;
    }

    int find_block_flow(int vertex, int min_cap) {
        if (vertex == sink_idx || min_cap == 0)
            return min_cap;

        for (int edge_i = nodes[vertex].first_save_edge; edge_i < (nodes[vertex].edges).size(); edge_i++) {
            Edge &edge = nodes[vertex].edges[edge_i];
            Edge &rev_edge = nodes[edge.to].edges[edge.reverse_edge];

            if (nodes[edge.to].depth == nodes[vertex].depth + 1) {
                int delta = find_block_flow(edge.to, min(min_cap, edge.capacity - edge.flow));
                if (delta != 0) {
                    edge.flow += delta;
                    rev_edge.flow -= delta;
                    return delta;
                }
            }
            nodes[vertex].first_save_edge += 1;
        }
        return 0;
    }

    int find_max_flow() {
        int max_flow = 0;

        while (bfs_from_source()) {
            int flow = find_block_flow(source_idx, INF);
            while (flow != 0) {
                max_flow += flow;
                if (max_flow >= INF)
                    return INF;
                flow = find_block_flow(source_idx, INF);
            }
        }
        return max_flow;
    }

    vector<Node> nodes;
    int source_idx;
    int sink_idx;
};

int n, m;
vector<bool> visited;
vector<int> reach;
FlowNetwork network;
vector<vector<char>> base_map;

int in_edge(int i, int j) {
    return i * m + j;
}

int out_edge(int i, int j) {
    return i * m + j + n * m;
}

void dfs(int v) {
    visited[v] = true;
    reach.push_back(v);

    for (auto &ed: network.nodes[v].edges) {
        if (!visited[ed.to] && ed.flow < ed.capacity)
            dfs(ed.to);
    }
}

int main() {
    cin >> n >> m;
    network = FlowNetwork(MAX_SIZE);
    visited.assign(MAX_SIZE, false);

    base_map.assign(n, vector<char>(m));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            char tmp;
            cin >> tmp;
            base_map[i][j] = tmp;
            if (tmp == '-')
                network.add_direct_edge(in_edge(i, j), out_edge(i, j), INF, i, j);
            else if (tmp == '.')
                network.add_direct_edge(in_edge(i, j), out_edge(i, j), 1, i, j);
            else if (tmp == '#')
                network.add_direct_edge(in_edge(i, j), out_edge(i, j), 0, i, j);
            else if (tmp == 'A')
                network.source_idx = out_edge(i, j);
            else
                network.sink_idx = in_edge(i, j);
        }
    }

    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < m - 1; j++) {
            network.add_edge(out_edge(i, j), in_edge(i + 1, j), INF);
            network.add_edge(out_edge(i + 1, j), in_edge(i, j), INF);
            network.add_edge(out_edge(i, j), in_edge(i, j + 1), INF);
            network.add_edge(out_edge(i, j + 1), in_edge(i, j), INF);
        }

    for (int i = 0; i < n - 1; i++) {
        network.add_edge(out_edge(i, m - 1), in_edge(i + 1, m - 1), INF);
        network.add_edge(out_edge(i + 1, m - 1), in_edge(i, m - 1), INF);
    }

    for (int j = 0; j < m - 1; j++) {
        network.add_edge(out_edge(n - 1, j), in_edge(n - 1, j + 1), INF);
        network.add_edge(out_edge(n - 1, j + 1), in_edge(n - 1, j), INF);
    }

    int max_flow = network.find_max_flow();

    if (max_flow >= INF)
        cout << -1;
    else {
        cout << max_flow << '\n';

        dfs(network.source_idx);

        for (int vertex: reach) {
            for (auto &edge: network.nodes[vertex].edges) {
                if (!visited[edge.to] && edge.flow == 1)
                    base_map[edge.x][edge.y] = '+';
            }
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++)
                cout << base_map[i][j];
            if (i < n - 1)
                cout << '\n';
        }

    }
    return 0;
}
