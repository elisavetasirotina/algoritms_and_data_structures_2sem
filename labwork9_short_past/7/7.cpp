#include <iostream>
#include <climits>
#include <algorithm>

class Graph {
public:
    Graph(int input_V) : V(input_V) {
        matrix = new int*[V + 1];
        for (int i = 1; i <= V; ++i) {
            matrix[i] = new int[V + 1];
        }
    }

    void floyd_warshall() {
        for (int i = 1; i <= V; ++i) {
            for (int j = 1; j <= V; ++j) {
                if (i == j) {
                    matrix[i][j] = 0;
                } else if (matrix[i][j] == -1) {
                    matrix[i][j] = INT_MAX;
                }
            }
        }

        for (int k = 1; k <= V; ++k) {
            for (int i = 1; i <= V; ++i) {
                for (int j = 1; j <= V; ++j) {
                    if (matrix[i][k] != INT_MAX && matrix[k][j] != INT_MAX &&
                        matrix[i][k] + matrix[k][j] < matrix[i][j]) {
                        matrix[i][j] = matrix[i][k] + matrix[k][j];
                    }
                }
            }
        }

        int min_res = INT_MAX;
        int max_res = INT_MIN;

        for (int i = 1; i <= V; ++i) {
            int eccentricity = INT_MIN;
            for (int j = 1; j <= V; ++j) {
                if (i != j && matrix[i][j] != INT_MAX) {
                    eccentricity = std::max(eccentricity, matrix[i][j]);
                }
            }

            if (eccentricity != INT_MIN) {
                min_res = std::min(min_res, eccentricity);
                max_res = std::max(max_res, eccentricity);
            }
        }

        std::cout << max_res << '\n';
        std::cout << min_res << '\n';
    }


    int V;
    int** matrix;
};

int main() {
    int n;
    std::cin >> n;

    Graph graph(n);

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            std::cin >> graph.matrix[i][j];
        }
    }

    graph.floyd_warshall();

    return 0;
}