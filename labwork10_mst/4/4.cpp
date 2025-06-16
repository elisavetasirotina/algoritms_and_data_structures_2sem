#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <limits>

class Graph {
public:
    Graph(int input_V, std::pair<int, int>* coords) : V(input_V), coords(coords) {}

    double prima(int start) {
        std::vector<double> distance(V + 1, std::numeric_limits<double>::max());
        std::vector<bool> visited(V + 1, false);
        std::vector<int> parent(V + 1, 0);

        distance[start] = 0.0;
        double total_distance = 0.0;

        for (int count = 1; count <= V; ++count) {
            int u = -1;
            for (int v = 1; v <= V; ++v) {
                if (!visited[v] && (u == -1 || distance[v] < distance[u])) {
                    u = v;
                }
            }

            if (u == -1) break;

            visited[u] = true;
            if (parent[u] != 0) {
                total_distance += sqrt(pow(coords[u].first - coords[parent[u]].first, 2) +
                                       pow(coords[u].second - coords[parent[u]].second, 2));
            }

            for (int v = 1; v <= V; ++v) {
                if (u == v) continue;
                double weight = sqrt(pow(coords[u].first - coords[v].first, 2) +
                                     pow(coords[u].second - coords[v].second, 2));
                if (!visited[v] && weight < distance[v]) {
                    distance[v] = weight;
                    parent[v] = u;
                }
            }
        }

        return total_distance;
    }

private:
    int V;
    std::pair<int, int>* coords;
};

int main() {
    int n, x, y;
    std::cin >> n;
    std::pair<int, int>* coordinates = new std::pair<int, int>[n + 1];

    for (int i = 1; i <= n; ++i) {
        std::cin >> coordinates[i].first >> coordinates[i].second;
    }

    Graph graph(n, coordinates);
    double total_distance = graph.prima(1);

    std::cout << std::fixed << std::setprecision(6) << total_distance;

    return 0;
}