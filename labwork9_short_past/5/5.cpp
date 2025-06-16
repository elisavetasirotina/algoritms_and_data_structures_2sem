#include <iostream>
#include <vector>
#include <queue>
#include <climits>

struct Edge {
    int u, v;
    long long w;
};

class Graph {
public:
    Graph(int input_V, int input_E) : V(input_V), E(input_E) {
        cycle = new bool[V + 1]();
        distance = new long long[V + 1];
        edges = new Edge[E];
        g.resize(V + 1);
        
        for (int i = 0; i <= V; ++i) {
            distance[i] = LLONG_MAX;
        }
    }

    void bellman_ford(int start) {
        distance[start] = 0;

        for (int i = 1; i <= V - 1; ++i) {
            for (int j = 0; j < E; ++j) {
                Edge e = edges[j];
                if (distance[e.u] != LLONG_MAX && distance[e.u] + e.w < distance[e.v]) {
                    distance[e.v] = distance[e.u] + e.w;
                }
            }
        }

        for (int j = 0; j < E; ++j) {
            Edge e = edges[j];
            if (distance[e.u] != LLONG_MAX && distance[e.u] + e.w < distance[e.v]) {
                cycle[e.v] = true;
            }
        }

        std::queue<int> q;
        for (int i = 1; i <= V; ++i) {
            if (cycle[i]) {
                q.push(i);
            }
        }

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v : g[u]) {
                if (!cycle[v]) {
                    cycle[v] = true;
                    q.push(v);
                }
            }
        }
    }

    int V, E;
    bool* cycle;
    Edge* edges;
    long long* distance;
    std::vector<std::vector<int>> g;
};

int main() {
    int n, m, s;
    std::cin >> n >> m >> s;

    Graph graph(n, m);

    for (int i = 0; i < m; ++i) {
        int x, y;
        long long w;
        std::cin >> x >> y >> w;
        graph.edges[i] = {x, y, w};
        graph.g[x].push_back(y);
    }

    graph.bellman_ford(s);

    for (int i = 1; i <= n; ++i) {
        if (graph.cycle[i]) {
            std::cout << "-" << "\n";
        } else if (graph.distance[i] == LLONG_MAX) {
            std::cout << "*" << "\n";
        } else {
            std::cout << graph.distance[i] << "\n";
        }
    }

    return 0;
}