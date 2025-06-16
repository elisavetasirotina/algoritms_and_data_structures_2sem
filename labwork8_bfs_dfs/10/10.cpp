#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

struct Door {
    int v;
    int l;
    int r;
};

struct Interval {
    int L;
    int R;
};


class Graph {
public:
    Graph(int n, int m){
        this->N = n;
        this->M = m;
        this->N = n;
        this->M = m;
        this->list_of_adjacenc = std::vector<std::vector<Door>>(n + 1);
    }
    
    void addEdge(int u, int v, int l, int r) {
        list_of_adjacenc[u].push_back({v, l, r});
        list_of_adjacenc[v].push_back({u, l, r});
    }

    int countEscapeOptions() {
        std::vector<std::vector<Interval>> height(N + 1);
        std::queue<std::pair<int, Interval>> queue;

        queue.push({1, {1, 1000000}});
        height[1].push_back({1, 1000000});

        while (!queue.empty()) {
            std::pair<int, Interval> current = queue.front();
            queue.pop();
            int u = current.first, curL = current.second.L, curR = current.second.R;

            for (int i = 0; i < list_of_adjacenc[u].size(); ++i) {
                Door e = list_of_adjacenc[u][i];
                int newL = std::max(curL, e.l), newR = std::min(curR, e.r);
                if (newL > newR) {
                    continue;
                }

                bool dominated = false;
                for (int j = 0; j < height[e.v].size(); ++j) {
                    Interval s = height[e.v][j];
                    if (s.L <= newL && s.R >= newR) {
                        dominated = true;
                        break;
                    }
                }

                if (dominated) {
                    continue;
                }

                for (int k = 0; k < height[e.v].size(); ) {
                    if (newL <= height[e.v][k].L && newR >= height[e.v][k].R) {
                        height[e.v].erase(height[e.v].begin() + k);
                    } else {
                        k++;
                    }
                }


                height[e.v].push_back({newL, newR});
                queue.push({e.v, {newL, newR}});
            }
        }

        int ans = -1;
        for (int i = 0; i < height[N].size(); ++i) {
            Interval s = height[N][i];
            ans = std::max(ans, s.R - s.L + 1);
        }

        return ans;
    }

private:
    int N, M;
    std::vector<std::vector<Door>> list_of_adjacenc;
};


int main() {
    int n, m;
    std::cin >> n >> m;
    std::pair<int,int>* corridors = new std::pair<int,int>[m];
    
    for (int i = 0; i < m; i++){
        int u, v;
        std::cin >> u >> v;
        corridors[i] = {u, v};
    }
    
    std::pair<int,int>* intervals = new std::pair<int,int>[m];
    
    for (int i = 0; i < m; i++){
        int l, r;
        std::cin >> l >> r;
        intervals[i] = {l, r};
    }
    
    Graph g(n, m);
    
    for (int i = 0; i < m; i++){
        int u = corridors[i].first, v = corridors[i].second, l = intervals[i].first, r = intervals[i].second;
        g.addEdge(u, v, l, r);
    }
    
    std::cout << g.countEscapeOptions() << '\n';
    return 0;
}