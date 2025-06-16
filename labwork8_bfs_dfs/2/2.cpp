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

    bool BFS(int start, int end){
        std::queue<int> queue;
        bool* visited = new bool[this->V + 1]{false};
        visited[start] = false;
        queue.push(start);
        while(!queue.empty()){
            int current = queue.front();
            queue.pop();
            for (int i = 0; i < list_of_adjacency[current].size(); ++i){
                if (list_of_adjacency[current][i] == end){
                    return true;
                }
                if (!visited[list_of_adjacency[current][i]]) {
                    queue.push(list_of_adjacency[current][i]);
                    visited[list_of_adjacency[current][i]] = true;
                }
            }
        }
        return false;
    }

private:
    int V;
    std::vector<std::vector<int>> list_of_adjacency;
};

int main() {
    int v, e, n, start, end, start_bfs, end_bfs;
    std::cin >> v >> e >> n;
    Graph g(v);

    for (int i = 0; i < e; ++i) {
        std::cin >> start >> end;
        g.addEdge(start, end);
    }

    for(int i = 0; i < n; ++i){
        std::cin >> start_bfs >> end_bfs;
        if (g.BFS(start_bfs, end_bfs) && g.BFS(end_bfs, start_bfs)){
            std::cout << "YES" << '\n';
        } else{
            std::cout << "NO" << '\n';
        }
    }
    return 0;
}