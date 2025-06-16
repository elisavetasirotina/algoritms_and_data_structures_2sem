#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

class Graph {
public:
    Graph(int v) {
        this->V = v;
        list_of_adjacency = std::vector<std::vector<int>>(v + 1);
        transposed_list = std::vector<std::vector<int>>(v + 1);
        visited = new bool[v + 1]{false};
    }

    void addEdge(int v, int edge) {
        list_of_adjacency[v].push_back(edge);
        transposed_list[edge].push_back(v);
    }

    void findComponents() {
        std::stack<int> Stack;
        bool* local_visited = new bool[V + 1]{false};

        for (int i = 1; i <= V; i++) {
            if (!local_visited[i]) {
                fillOrder(i, local_visited, Stack);
            }
        }

        while (!Stack.empty()) {
            int v = Stack.top();
            Stack.pop();
            if (!visited[v]) {
                components.push_back(std::vector<int>());
                DFS(v);
            }
        }

        std::cout << components.size() << " ";
        findBridges();
    }

private:
    int V;
    std::vector<std::vector<int>> list_of_adjacency;
    std::vector<std::vector<int>> transposed_list;
    bool* visited;
    std::vector<std::vector<int>> components;
    std::vector<std::pair<int, int>> bridges;

    void fillOrder(int current, bool* local_visited, std::stack<int>& Stack) {
        local_visited[current] = true;
        for (int i = 0; i < list_of_adjacency[current].size(); i++) {
            int neighbor = list_of_adjacency[current][i];
            if (!local_visited[neighbor]) {
                fillOrder(neighbor, local_visited, Stack);
            }
        }
        Stack.push(current);
    }

    void DFS(int current) {
        visited[current] = true;
        components[components.size() - 1].push_back(current);
        for (int i = 0; i < transposed_list[current].size(); i++) {
            int neighbor = transposed_list[current][i];
            if (!visited[neighbor]) {
                DFS(neighbor);
            }
        }
    }

    void findBridges() {
        std::vector<int> component_number(V + 1, -1);
        std::vector<int> min_house(components.size());
        for (int i = 0; i < min_house.size(); i++) {
            min_house[i] = V + 1;
        }

        for (int i = 0; i < components.size(); i++) {
            for (int j = 0; j < components[i].size(); j++) {
                int house = components[i][j];
                component_number[house] = i;
                if (house < min_house[i]) {
                    min_house[i] = house;
                }
            }
        }

        for (int i = 0; i < components.size(); i++) {
            for (int j = 0; j < components[i].size(); j++) {
                int house = components[i][j];
                component_number[house] = min_house[i];
            }
        }

        for (int i = 1; i <= V; i++) {
            for (int j = 0; j < list_of_adjacency[i].size(); j++) {
                int neighbor = list_of_adjacency[i][j];
                if (component_number[i] != component_number[neighbor]) {
                    bridges.push_back(std::pair<int, int>(component_number[i], component_number[neighbor]));
                }
            }
        }

        removeDuplicates();
    }

    void removeDuplicates() {
        std::sort(bridges.begin(), bridges.end());

        std::vector<std::pair<int, int>> unique_bridges;
        for (int i = 0; i < bridges.size(); i++) {
            if (i == 0 || bridges[i] != bridges[i - 1]) {
                unique_bridges.push_back(bridges[i]);
            }
        }

        std::cout << unique_bridges.size() << '\n';
        for (int i = 0; i < unique_bridges.size(); i++) {
            std::cout << unique_bridges[i].first << " " << unique_bridges[i].second << '\n';
        }
    }
};

int main() {
    int v, e;
    std::cin >> v >> e;
    Graph g(v);

    for (int i = 0; i < e; i++) {
        int start, end;
        std::cin >> start >> end;
        g.addEdge(start, end);
    }

    g.findComponents();
    return 0;
}
