#include <iostream>
#include <queue>
#include <vector>

class Graph {
public:
    Graph(int v){
        this->V = v;
        this->list_of_adjacency = std::vector<std::vector<int>>(v + 1);
    }

    void addEdge(int v, int edge) {
        list_of_adjacency[v].push_back(edge);
    }

    int countComponents() {
        int count = 0;
        bool* visited = new bool[this->V + 1]{false};

        for (int i = 1; i <= this->V; i++) {
            if (!visited[i]) {
                BFS(i, visited);
                count++;
            }
        }
        return count;
    }

private:
    int V;
    std::vector<std::vector<int>> list_of_adjacency;

    void BFS(int start, bool*& visited) {
        std::queue<int> queue;
        queue.push(start);
        visited[start] = true;

        while (!queue.empty()) {
            int current = queue.front();
            queue.pop();
            for (int i = 0; i <list_of_adjacency[current].size(); i++) {
                int neighbor = list_of_adjacency[current][i];
                if (!visited[neighbor]) {
                    queue.push(neighbor);
                    visited[neighbor] = true;
                }
            }
        }
    }
};

int main() {
    int v, e, start, end;
    std::cin >> v >> e;
    Graph g(v);

    for (int i = 0; i < e; ++i) {
        std::cin >> start >> end;
        g.addEdge(start, end);
        g.addEdge(end, start);
    }

    std::cout << g.countComponents();
    return 0;
}
