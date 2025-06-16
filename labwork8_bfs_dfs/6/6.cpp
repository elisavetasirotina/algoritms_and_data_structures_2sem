#include <iostream>
#include <vector>
#include <queue>

class Graph {
public:
    Graph(int v) {
        this->V = v;
        this->list_of_adjacency = std::vector<std::vector<int>>(v + 1);
        this->visited = new bool[v + 1]{false};
        this->distance = new int[v + 1]{-1};
    }

    void addEdge(int v, int edge) {
        list_of_adjacency[v].push_back(edge);
        list_of_adjacency[edge].push_back(v);
    }

    void BFS(int start, int k) {
        distance[start] = 0;
        visited[start] = true;
        std::queue<int> queue;
        queue.push(start);

        while (!queue.empty()) {
            int top = queue.front();
            queue.pop();

            for (int i = 0; i < list_of_adjacency[top].size(); ++i) {
                int neighbor = list_of_adjacency[top][i];

                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    distance[neighbor] = distance[top] + 1;
                    queue.push(neighbor);
                }
            }
        }

        bool flag = false;
        for (int i = 1; i <= V; ++i) {
            if (distance[i] == k) {
                std::cout << i << '\n';
                flag = true;
            }
        }

        if (!flag) {
            std::cout << "NO";
        }
    }

private:
    int V;
    std::vector<std::vector<int>> list_of_adjacency;
    bool* visited;
    int* distance;
};

int main() {
    int v, e, k, start, end;
    std::cin >> v >> e >> k;
    Graph g(v);

    for (int i = 0; i < e; ++i) {
        std::cin >> start >> end;
        g.addEdge(start, end);
    }

    g.BFS(1, k);
    return 0;
}
