#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <iomanip>
#include <climits>

class Graph {
public:
    Graph(int input_V) {
        this->V = input_V;
        this->adj_list = new std::vector<std::pair<int, long long>>[V + 1];
        this->distance = new long long[V + 1];
        this->visited = new bool[V + 1]{false};
        this->parent = new int[V + 1];

        for (int i = 1; i <= V; ++i) {
            distance[i] = LLONG_MAX;
            parent[i] = -1;
        }
    }

    void add_edge(int u, int v, long long w) {
        adj_list[u].push_back({v, w});
        adj_list[v].push_back({u, w});
    }

    long long prima(int start, int& edges_count, std::vector<std::pair<int, int>>& mst_edges) {
        std::priority_queue<std::pair<long long, int>, std::vector<std::pair<long long, int>>, std::greater<std::pair<long long, int>>> pq;
        distance[start] = 0;
        pq.push({0, start});

        long long total_weight = 0;

        while (!pq.empty()) {
            long long dist_sq = pq.top().first;
            int u = pq.top().second;
            pq.pop();

            if (visited[u]) {
                continue;
            }

            visited[u] = true;
            total_weight += dist_sq;

            if (parent[u] != -1) {
                mst_edges.push_back({u, parent[u]});
                edges_count++;
            }

            for (std::pair<int, long long> neighbor : adj_list[u]) {
                int v = neighbor.first;
                long long weight_sq = neighbor.second;

                if (!visited[v] && weight_sq < distance[v]) {
                    distance[v] = weight_sq;
                    pq.push({weight_sq, v});
                    parent[v] = u;
                }
            }
        }

        return total_weight;
    }

    int V;
    std::vector<std::pair<int, long long>>* adj_list;
    long long* distance;
    bool* visited;
    int* parent;
};


double calculateDistance(int x1, int y1, int x2, int y2) {
    return std::sqrt(std::pow(x1 - x2, 2) + std::pow(y1 - y2, 2));
}

int main() {
    int n, x, y;
    std::cin >> n;
    std::pair<int, int>* coordinates = new std::pair<int, int>[n + 1];

    for (int i = 1; i <= n; ++i) {
        std::cin >> coordinates[i].first >> coordinates[i].second;
    }

    Graph graph(n);

    for (int i = 1; i <= n; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            long long weight_sq = (long long)std::pow(coordinates[i].first - coordinates[j].first, 2) +
                                  (long long)std::pow(coordinates[i].second - coordinates[j].second, 2);
            graph.add_edge(i, j, weight_sq);
        }
    }

    int edges_count = 0;
    std::vector<std::pair<int, int>> mst_edges;
    long long total_weight_sq = graph.prima(1, edges_count, mst_edges);

    double total_distance = 0.0;
    for (std::pair<int, int> edge : mst_edges) {
        total_distance += calculateDistance(coordinates[edge.first].first, coordinates[edge.first].second,
                                            coordinates[edge.second].first, coordinates[edge.second].second);
    }

    std::cout << std::fixed << std::setprecision(6) << total_distance << '\n';
    std::cout << edges_count << '\n';

    for (std::pair<int, int> edge : mst_edges) {
        std::cout << edge.first << " " << edge.second << '\n';
    }

    return 0;
}