#include <iostream>
#include <vector>
#include <climits>

class Graph {
public:
    Graph(int input_V) {
        this->V = input_V;
        this->visited = new bool[this->V + 1]{false};
        this->distance = new int[this->V + 1];
        for (int i = 1; i <= V; ++i) {
            distance[i] = INT_MAX;
        }
        this->matrix = new int*[V + 1];
        for (int i = 1; i <= V; ++i) {
            matrix[i] = new int[V + 1];
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
                }
            }
        }

        return (distance[end] == INT_MAX) ? -1 : distance[end];
    }

    int V;
    int* distance;
    bool* visited;
    int** matrix;
};

int main() {
    int n, s, f;
    std::cin >> n >> s >> f;
    Graph graph(n);

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            std::cin >> graph.matrix[i][j];
        }
    }

    std::cout << graph.dijkstra(s, f);
    return 0;
}