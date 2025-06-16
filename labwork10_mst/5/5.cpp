#include <iostream>
#include <vector>
#include <algorithm>

struct Edge {
    long long cost;
    int u;
    int v;
};

bool compareEdges(Edge a, Edge b) {
    return a.cost < b.cost;
}

class Graph {
public:
    Graph(int input_n, int* input_x, int* input_y, long long* input_c, long long* input_k)
            : n(input_n), x(input_x), y(input_y), c(input_c), k(input_k) {}

    void calculate() {
        std::vector<Edge> edges;

        for (int i = 0; i < n; ++i) {
            Edge e = {c[i], 0, i + 1};
            edges.push_back(e);
        }

        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                long long cost = (long long)(abs(x[i] - x[j]) + abs(y[i] - y[j])) * (k[i] + k[j]);
                Edge e = {cost, i + 1, j + 1};
                edges.push_back(e);
            }
        }

        std::sort(edges.begin(), edges.end(), compareEdges);

        std::vector<int> parent(n + 1);
        for (int i = 0; i <= n; ++i) {
            parent[i] = i;
        }

        long long total_cost = 0;
        std::vector<int> stations;
        std::vector<std::pair<int, int>> lines;

        for (Edge edge : edges) {
            int rootU = find(parent, edge.u);
            int rootV = find(parent, edge.v);

            if (rootU != rootV) {
                total_cost += edge.cost;
                unite(parent, edge.u, edge.v);

                if (edge.u == 0) {
                    stations.push_back(edge.v);
                } else if (edge.v == 0) {
                    stations.push_back(edge.u);
                } else {
                    lines.push_back({edge.u, edge.v});
                }
            }
        }

        std::cout << total_cost << '\n';
        std::cout << stations.size() << '\n';

        std::sort(stations.begin(), stations.end());

        for (int station : stations) {
            std::cout << station << " ";
        }
        std::cout << '\n';

        std::cout << lines.size() << '\n';
        for (std::pair<int, int> line : lines) {
            std::cout << line.first << " " << line.second << '\n';
        }
    }

private:
    int n;
    int* x;
    int* y;
    long long* c;
    long long* k;

    int find(std::vector<int>& parent, int v) {
        if (v == parent[v]) {
            return v;
        }
        return parent[v] = find(parent, parent[v]);
    }

    void unite(std::vector<int>& parent, int a, int b) {
        int rootA = find(parent, a);
        int rootB = find(parent, b);
        if (rootA != rootB) {
            parent[rootB] = rootA;
        }
    }
};

int main() {
    int n;
    std::cin >> n;

    int* x = new int[n];
    int* y = new int[n];
    for (int i = 0; i < n; ++i) {
        std::cin >> x[i] >> y[i];
    }

    long long* c = new long long[n];
    for (int i = 0; i < n; ++i) {
        std::cin >> c[i];
    }

    long long* k = new long long[n];
    for (int i = 0; i < n; ++i) {
        std::cin >> k[i];
    }

    Graph graph(n, x, y, c, k);
    graph.calculate();

    return 0;
}