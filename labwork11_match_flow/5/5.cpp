#include <iostream>
#include <queue>
#include <vector>
#include <climits>


struct Edge {
    int to;
    int rev;
    int flow;
    int capacity;

    Edge(int t, int r, int c) : to(t), rev(r), capacity(c), flow(0) {}
};

std::vector<std::vector<Edge>> adj;

void addEdge(int u, int v, int c) {
    adj[u].emplace_back(v, adj[v].size(), c);
    adj[v].emplace_back(u, adj[u].size() - 1, 0);
}

int bfs(int s, int t, std::vector<int>& parent, std::vector<int>& parentEdge) {
    std::fill(parent.begin(), parent.end(), -1);
    std::fill(parentEdge.begin(), parentEdge.end(), -1);
    std::queue<std::pair<int, int>> q;
    q.push({s, INT_MAX});
    parent[s] = s;

    while (!q.empty()) {
        int u = q.front().first;
        int min_flow = q.front().second;
        q.pop();

        for (int i = 0; i < adj[u].size(); ++i) {
            Edge& e = adj[u][i];
            if (parent[e.to] == -1 && e.capacity > e.flow) {
                parent[e.to] = u;
                parentEdge[e.to] = i;
                int new_flow = std::min(min_flow, e.capacity - e.flow);
                if (e.to == t) {
                    return new_flow;
                }
                q.push({e.to, new_flow});
            }
        }
    }
    return 0;
}


int maxFlow(int s, int t) {
    int flow = 0;
    std::vector<int> parent(adj.size());
    std::vector<int> parentEdge(adj.size());

    while (true) {
        int pushed = bfs(s, t, parent, parentEdge);
        if (pushed == 0) break;

        flow += pushed;
        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            int ei = parentEdge[v];
            adj[u][ei].flow += pushed;
            int rev = adj[u][ei].rev;
            adj[v][rev].flow -= pushed;
        }
    }
    return flow;
}


int main() {
    int n, m, w, b, g;
    std::cin >> n >> m >> w >> b >> g;

    std::vector<std::string> grid(n);
    for (int i = 0; i < n; ++i)
        std::cin >> grid[i];

    int s = 0;
    int t = 1;
    int nodes = n * m + 2;

    adj.resize(nodes);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            int node = 2 + i * m + j;

            if (grid[i][j] == 'B') {
                addEdge(node, t, w);
            } else if (grid[i][j] == 'W'){
                addEdge(s, node, b);
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            int node = 2 + i * m + j;
            if (j < m - 1) {
                int right = node + 1;
                addEdge(node, right, g);
                addEdge(right, node, g);
            }

            if (i < n - 1) {
                int down = node + m;
                addEdge(node, down, g);
                addEdge(down, node, g);
            }
        }
    }

    std::cout << maxFlow(s, t);
    return 0;
}