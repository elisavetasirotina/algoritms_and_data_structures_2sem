#include <iostream>
#include <vector>
#include <stack>

class Graph {
public:
    Graph(int v) {
        V = v;
        adjacency_list = new std::vector<int>[2 * V + 2];
        transposed_list = new std::vector<int>[2 * V + 2];
        visited = new bool[2 * V + 2];
        component = new int[2 * V + 2];

        for (int i = 0; i < 2 * V + 2; ++i) {
            visited[i] = false;
            component[i] = -1;
        }
    }

    void addEdge(int v, int edge) {
        adjacency_list[v].push_back(edge);
        transposed_list[edge].push_back(v);
    }

    void fillOrder(int v, std::stack<int>& Stack) {
        visited[v] = true;
        for (int i = 0; i < adjacency_list[v].size(); ++i) {
            int neighbour = adjacency_list[v][i];
            if (!visited[neighbour]) {
                fillOrder(neighbour, Stack);
            }
        }
        Stack.push(v);
    }

    void findComponent(int v, int count) {
        visited[v] = true;
        component[v] = count;
        for (int i = 0; i < transposed_list[v].size(); ++i) {
            int neighbour = transposed_list[v][i];
            if (!visited[neighbour]) {
                findComponent(neighbour, count);
            }
        }
    }

    void findComponents() {
        std::stack<int> Stack;

        for (int i = 0; i <= 2 * V + 1; ++i) {
            visited[i] = false;
        }

        for (int i = 1; i <= 2 * V; ++i) {
            if (!visited[i]) {
                fillOrder(i, Stack);
            }
        }

        for (int i = 0; i <= 2 * V + 1; ++i) {
            visited[i] = false;
        }

        int count = 0;
        while (!Stack.empty()) {
            int v = Stack.top();
            Stack.pop();
            if (!visited[v]) {
                findComponent(v, count);
                count++;
            }
        }
    }

    bool Check() {
        for (int i = 1; i <= V; ++i) {
            if (component[i] == component[i + V]) {
                return false;
            }
        }
        return true;
    }

private:
    int V;
    std::vector<int>* adjacency_list;
    std::vector<int>* transposed_list;
    bool* visited;
    int* component;
};

int main() {
    int n, k, ing1, ing2;
    std::cin >> n >> k;
    Graph g(n);

    for (int i = 0; i < k; ++i) {
        std::string str;
        std::cin >> str;

        if (str[0] == '!') {
            ing1 = std::stoi(str.substr(1));
            g.addEdge(ing1, ing1 + n);
        } else {
            std::string operation;
            std::cin >> operation >> ing2;
            ing1 = std::stoi(str);

            if (operation == "->") {
                g.addEdge(ing1, ing2);
                g.addEdge(ing2 + n, ing1 + n);
            } else if (operation == "||") {
                g.addEdge(ing1 + n, ing2);
                g.addEdge(ing2 + n, ing1);
            } else if (operation == "^") {
                g.addEdge(ing1 + n, ing2);
                g.addEdge(ing1, ing2 + n);
                g.addEdge(ing2 + n, ing1);
                g.addEdge(ing2, ing1 + n);
            } else if (operation == "&") {
                g.addEdge(ing1 + n, ing2 + n);
                g.addEdge(ing2 + n, ing1 + n);
                g.addEdge(ing1 + n, ing2);
                g.addEdge(ing2 + n, ing1);
                g.addEdge(ing1, ing2);
                g.addEdge(ing2, ing1);
            }
        }
    }

    g.findComponents();

    if (g.Check()) {
        std::cout << "YES";
    } else {
        std::cout << "NO";
    }

    return 0;
}
