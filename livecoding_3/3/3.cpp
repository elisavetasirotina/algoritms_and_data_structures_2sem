#include <iostream>
#include <algorithm>

class Graph {
public:
    Graph(int input_V) : V(input_V) {
        matrix = new int*[V+1];
        for (int i = 1; i <= V; ++i)
            matrix[i] = new int[V+1];
    }

    void floyd() {
        for (int k = 1; k <= V; ++k) {
            for (int i = 1; i <= V; ++i) {
                for (int j = 1; j <= V; ++j) {
                    int via_k = std::max(matrix[i][k], matrix[k][j]);
                    if (via_k < matrix[i][j])
                        matrix[i][j] = via_k;
                }
            }
        }

        int answer = 0;
        for (int i = 1; i <= V; ++i) {
            for (int j = 1; j <= V; ++j) {
                answer = std::max(answer, matrix[i][j]);
            }
        }
        std::cout << answer;
    }

    int V;
    int** matrix;
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;
    Graph graph(n);
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            std::cin >> graph.matrix[i][j];
        }
    }
    graph.floyd();
    return 0;
}
