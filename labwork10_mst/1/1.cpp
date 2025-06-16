#include <iostream>
#include <algorithm>

class Graph {
public:
    Graph(int input_V, int input_m) {
        this->V = input_V;
        this->m = input_m;
        parent = new int[V + 1];
        rank = new int[V + 1];
        edges = new int*[m];

        for (int i = 1; i <= V; ++i) {
            parent[i] = i;
            rank[i] = 0;
        }

        edge_count = 0;
    }

    void add_edge(int u, int v, int w) {
        edges[edge_count] = new int[3];
        edges[edge_count][0] = w;
        edges[edge_count][1] = u;
        edges[edge_count][2] = v;
        ++edge_count;
    }

    int find(int u) {
        while (parent[u] != u) {
            u = parent[u];
        }
        return u;
    }

    void union_sets(int u, int v) {
        int root_u = find(u);
        int root_v = find(v);

        if (root_u != root_v) {
            if (rank[root_u] < rank[root_v]) {
                parent[root_u] = root_v;
            } else if (rank[root_u] > rank[root_v]) {
                parent[root_v] = root_u;
            } else {
                parent[root_v] = root_u;
                ++rank[root_u];
            }
        }
    }

    long long kruskal() {
        std::sort(edges, edges + edge_count, compare);

        long long total_weight = 0;
        int edges_used = 0;

        for (int i = 0; i < edge_count; ++i) {
            int w = edges[i][0];
            int u = edges[i][1];
            int v = edges[i][2];

            if (find(u) != find(v)) {
                union_sets(u, v);
                total_weight += w;
                edges_used++;

                if (edges_used == V - 1) {
                    break;
                }
            }
        }

        return total_weight;
    }

private:
    int V, m;
    int *parent, *rank;
    int **edges;
    int edge_count;

    static bool compare(int* a, int* b) {
        return a[0] < b[0];
    }
};

int main() {
    int n, m, x, y, w;
    std::cin >> n >> m;

    Graph graph(n, m);

    for (int i = 0; i < m; ++i) {
        std::cin >> x >> y >> w;
        graph.add_edge(x, y, w);
    }

    std::cout << graph.kruskal() << '\n';

    return 0;
}
