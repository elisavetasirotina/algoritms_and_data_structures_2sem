#include <iostream>
#include <iomanip>
#include <limits>

struct Edge {
    int from, to;
    double rate;
    double commission;
};

class Graph {
public:
    Graph(int n, int m) : V(n), E(2 * m) {
        edges = new Edge[E];
    }

    void add_edge(int idx, int a, int b, double r_ab, double c_ab, double r_ba, double c_ba) {
        edges[idx * 2] = {a, b, r_ab, c_ab};
        edges[idx * 2 + 1] = {b, a, r_ba, c_ba};
    }

    bool can_increase_capital(int start, double initial_amount) {
        double* max_amount = new double[V + 1];
        for (int i = 1; i <= V; ++i) {
            max_amount[i] = std::numeric_limits<double>::lowest();
        }
        max_amount[start] = initial_amount;

        for (int i = 0; i <= V; ++i) {
            bool updated = false;

            for (int j = 0; j < E; ++j) {
                Edge edge = edges[j];
                int u = edge.from;
                int v = edge.to;

                if (max_amount[u] > edge.commission) {
                    double new_amount = (max_amount[u] - edge.commission) * edge.rate;

                    if (new_amount > max_amount[v]) {
                        max_amount[v] = new_amount;
                        updated = true;
                    }
                }
            }

            if (!updated) {
                break;
            }

            if (i == V && updated) {
                delete[] max_amount;
                return true;
            }
        }
        return false;
    }

private:
    int V, E;
    Edge* edges;
};

int main() {
    int n, m, s;
    double v;
    std::cin >> n >> m >> s >> v;

    Graph graph(n, m);

    for (int i = 0; i < m; ++i) {
        int a, b;
        double r_ab, c_ab, r_ba, c_ba;
        std::cin >> a >> b >> r_ab >> c_ab >> r_ba >> c_ba;
        graph.add_edge(i, a, b, r_ab, c_ab, r_ba, c_ba);
    }

    if (graph.can_increase_capital(s, v)) {
        std::cout << "YES" << '\n';
    } else {
        std::cout << "NO" << '\n';
    }

    return 0;
}