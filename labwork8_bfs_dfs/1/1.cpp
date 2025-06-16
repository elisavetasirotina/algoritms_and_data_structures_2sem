#include <iostream>
#include <stack>
#include <vector>

class Graph {
public:
    int* sort;

    Graph(int v){
        this->V = v;
        this->list_of_adjacency = std::vector<std::vector<int>>(v + 1);
        this->sort = new int[v + 1];
        this->index = v;
    }

    void addEdge(int v, int edge) {
        list_of_adjacency[v].push_back(edge);
    }

    void topologicalSort() {
        std::stack<int> Stack;
        bool* visited = new bool[V + 1]{false};

        for (int i = 1; i <= V; i++) {
            if (!visited[i]) {
                topologicalSortUtil(i, visited, Stack);
            }
        }

        int pos = 1;
        while (!Stack.empty()) {
            sort[Stack.top()] = pos++;
            Stack.pop();
        }
    }

private:
    int V;
    std::vector<std::vector<int>> list_of_adjacency;
    int index;

    void topologicalSortUtil(int v, bool*& visited, std::stack<int>& Stack) {
        visited[v] = true;

        for (int i = 0; i < list_of_adjacency[v].size(); i++) {
            int neighbor = list_of_adjacency[v][i];
            if (!visited[neighbor]) {
                topologicalSortUtil(neighbor, visited, Stack);
            }
        }

        Stack.push(v);
    }
};

int main() {
    int v, n, a, b;
    std::cin >> v >> n;
    Graph g(v);

    for (int i = 0; i < n; ++i) {
        std::cin >> a >> b;
        g.addEdge(a, b);
    }

    g.topologicalSort();

    for (int i = 1; i <= v; ++i) {
        if (i > 1) std::cout << " ";
        std::cout << g.sort[i];
    }
    return 0;
}