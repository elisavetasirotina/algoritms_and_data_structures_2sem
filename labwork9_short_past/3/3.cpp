#include <iostream>
#include <vector>
#include <queue>
#include <climits>

class Graph {
public:
    Graph(int input_V) {
        this->V = input_V;
        this->adj_list = new std::vector<std::pair<int, int>>[V + 1];
        this->distance = new int[V + 1];
        this->visited = new bool[V + 1]{false};

        for (int i = 1; i <= V; ++i) {
            distance[i] = INT_MAX;
        }
    }

    void add_edge(int u, int v, int w) {
        adj_list[u].push_back({v, w});
        adj_list[v].push_back({u, w});
    }

    int dijkstra(int start, int end) {
        std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;
        distance[start] = 0;
        pq.push({0, start});

        while (!pq.empty()) {
            int dist = pq.top().first;
            int min_v = pq.top().second;
            pq.pop();

            if (!visited[min_v]) {
                visited[min_v] = true;

                for (auto& neighbor : adj_list[min_v]) {
                    int to = neighbor.first;
                    int weight = neighbor.second;

                    if (distance[min_v] + weight < distance[to]) {
                        distance[to] = distance[min_v] + weight;
                        pq.push({distance[to], to});
                    }
                }
            }
        }

        return (distance[end] == INT_MAX) ? -1 : distance[end];
    }

    int V;
    std::vector<std::pair<int, int>>* adj_list;
    int* distance;
    bool* visited;
};

int main() {
    int n, m, s, f, x, y, w;
    std::cin >> n >> m;
    std::cin >> s >> f;

    Graph graph(n);

    for (int i = 0; i < m; ++i) {
        std::cin >> x >> y >> w;
        graph.add_edge(x, y, w);
    }

    std::cout << graph.dijkstra(s, f);

    return 0;
}
