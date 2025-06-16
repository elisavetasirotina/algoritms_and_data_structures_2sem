#include <iostream>
#include <vector>
#include <queue>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;

    std::vector<std::vector<int>> g(n);
    std::vector<int> degree(n, 0);
    for (int i = 0; i < m; ++i) {
        int a, b;
        std::cin >> a >> b;
        g[a - 1].push_back(b - 1);
        degree[b - 1]++;
    }

    std::queue<int> q;
    for (int i = 0; i < n; ++i) {
        if (degree[i] == 0)
            q.push(i);
    }

    std::vector<int> res;
    while (!q.empty()) {
        if (q.size() > 1) {
            std::cout << "NO";
            return 0;
        }
        int v = q.front();
        q.pop();
        res.push_back(v + 1);

        for (int u : g[v]) {
            degree[u]--;
            if (degree[u] == 0) {
                q.push(u);
            }
        }
    }

    if (res.size() == n) {
        std::cout << "YES" << "\n";
        for (int x : res)
            std::cout << x << " ";
        std::cout << "\n";
    } else {
        std::cout << "NO";
    }

    return 0;
}
