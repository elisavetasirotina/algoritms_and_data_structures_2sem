#include <iostream>
#include <vector>
#include <climits>


class Graph {
public:
    Graph(int input_V) {
        this->V = input_V;
        this->visited = new bool[this->V + 1]{false};
        this->distance = new int[this->V + 1];
        this->parent = new int[this->V + 1]{0};

        for (int i = 1; i <= V; ++i) {
            distance[i] = INT_MAX;
        }

        this->matrix = new int*[V + 1];
        for (int i = 1; i <= V; ++i) {
            matrix[i] = new int[V + 1];
            for (int j = 1; j <= V; ++j) {
                matrix[i][j] = -1;
            }
        }
    }

    int dijkstra(int start, int end) {
        distance[start] = 0;

        for (int i = 1; i <= V; ++i) {
            int min_v = -1;

            for (int j = 1; j <= V; ++j) {
                if (!visited[j] && (min_v == -1 || distance[j] < distance[min_v])) {
                    min_v = j;
                }
            }

            if (min_v == -1 || distance[min_v] == INT_MAX) {
                break;
            }

            visited[min_v] = true;

            for (int e = 1; e <= V; ++e) {
                if (matrix[min_v][e] >= 0 && distance[min_v] + matrix[min_v][e] < distance[e]) {
                    distance[e] = distance[min_v] + matrix[min_v][e];
                    parent[e] = min_v;
                }
            }
        }

        return (distance[end] == INT_MAX) ? -1 : distance[end];
    }

    int V;
    int* distance;
    bool* visited;
    int** matrix;
    int* parent;
};

int main() {
    int n, m, s, f, x, y, w;
    std::cin >> n >> m;
    std::cin >> s >> f;

    Graph graph(n);

    for (int i = 0; i < m; ++i) {
        std::cin >> x >> y >> w;
        graph.matrix[x][y] = w;
        graph.matrix[y][x] = w;
    }

    int result = graph.dijkstra(s, f);

    if (result == -1) {
        std::cout << -1;
        return 0;
    }

    std::cout << result << '\n';

    std::vector<int> path;
    for (int current = f; current != 0; current = graph.parent[current]) {
        path.push_back(current);
        if (current == s) break;
    }

    if (path.back() != s) {
        std::cout << -1;
        return 0;
    }

    for (int i = path.size() - 1; i >= 0; --i) {
        std::cout << path[i] << " ";
    }

    return 0;
}
