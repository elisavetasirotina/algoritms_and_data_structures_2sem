#include <iostream>
#include <vector>
#include <stack>

class Graph {
public:
    Graph(int v) {
        this->V = v;
        this->list_of_adjacency = std::vector<std::vector<int>>(v + 1);
        this->visited = new bool[v + 1]{false};
    }

    void addEdge(int v, int edge) {
        this->list_of_adjacency[v].push_back(edge);
        this->list_of_adjacency[edge].push_back(v);
    }

    void DFS() {
        for (int i = 1; i <= this->V; ++i) {
            if (!visited[i]) {
                if (DFS(i, -1)) {
                    std::cout << "YES";
                    return;
                }
            }
        }
        std::cout << "NO";
    }

private:
    int V;
    std::vector<std::vector<int>> list_of_adjacency;
    bool* visited;

    bool DFS(int current, int parent) {
        this->visited[current] = true;
        for (int neighbour : this->list_of_adjacency[current]) {
            if (!visited[neighbour]) {
                if (DFS(neighbour, current)) {
                    return true;
                }
            } else if (neighbour != parent) {
                return true;
            }
        }
        return false;
    }
};

int main() {
    int v, e, start, end;
    std::cin >> v >> e;
    Graph g(v);

    for (int i = 0; i < e; ++i) {
        std::cin >> start >> end;
        g.addEdge(start, end);
    }

    g.DFS();

    return 0;
}
