#include <iostream>
#include <vector>

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

    bool DFS(int current, int parent) {
        this->visited[current] = true;
        for (int i = 0; i < this->list_of_adjacency[current].size(); ++i) {
            int neighbour = list_of_adjacency[current][i];
            if (!visited[neighbour]) {
                DFS(neighbour, current);
            }
        }
        for (int i = 1; i < this->V + 1; ++i){
            if (!this->visited[i]){
                return false;
            }
        }
        return true;
    }

private:
    int V;
    std::vector<std::vector<int>> list_of_adjacency;
    bool* visited;
};

int main() {
    int v, e, start, end;
    std::cin >> v >> e;
    Graph g(v);

    for (int i = 0; i < e; ++i) {
        std::cin >> start >> end;
        g.addEdge(start, end);
    }

    if (v != e) {
        std::cout << "EUCLID";
        return 0;
    }

    if (g.DFS(1, -1)){
        std::cout << "ARCHIMEDES";
    } else{
        std::cout << "EUCLID";
    }

    return 0;
}
