#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

class HopcroftKarp {
public:
    int n1, n2;
    std::vector<std::vector<int>> g;
    std::vector<int> match, matchLeft, dist;

    HopcroftKarp(int n1, int n2) : n1(n1), n2(n2) {
        g.resize(n1);
        matchLeft.assign(n1, -1);
        match.assign(n2, -1);
        dist.resize(n1);
    }

    void add_edge(int u, int v) {
        g[u].push_back(v);
    }

    bool bfs() {
        std::queue<int> q;
        for (int u = 0; u < n1; ++u) {
            if (matchLeft[u] == -1) {
                dist[u] = 0;
                q.push(u);
            } else {
                dist[u] = -1;
            }
        }

        bool found = false;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v : g[u]) {
                if (match[v] == -1) {
                    found = true;
                } else if (dist[match[v]] == -1) {
                    dist[match[v]] = dist[u] + 1;
                    q.push(match[v]);
                }
            }
        }
        return found;
    }

    bool dfs(int u) {
        for (int v : g[u]) {
            if (match[v] == -1 || (dist[match[v]] == dist[u] + 1 && dfs(match[v]))) {
                matchLeft[u] = v;
                match[v] = u;
                return true;
            }
        }
        dist[u] = -1;
        return false;
    }

    int max_matching() {
        int result = 0;
        while (bfs()) {
            for (int u = 0; u < n1; ++u) {
                if (matchLeft[u] == -1 && dfs(u)) {
                    ++result;
                }
            }
        }
        return result;
    }
};

int solve(int n1, int n2, const std::vector<std::pair<int, int>>& edges,
          const std::vector<bool>& skipLeft, const std::vector<bool>& skipRight) {
    HopcroftKarp hk(n1, n2);
    for (auto [u, v] : edges) {
        if (!skipLeft[u] && !skipRight[v]) {
            hk.add_edge(u, v);
        }
    }
    return hk.max_matching();
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n1, n2, m;
    std::cin >> n1 >> n2 >> m;
    std::vector<std::pair<int, int>> edges(m);
    for (int i = 0; i < m; ++i) {
        int u, v;
        std::cin >> u >> v;
        --u;
        --v;
        edges[i] = {u, v};
    }

    std::vector<bool> skipLeft(n1, false), skipRight(n2, false);
    int base_matching = solve(n1, n2, edges, skipLeft, skipRight);

    std::string resLeft(n1, 'P'), resRight(n2, 'P');

    for (int i = 0; i < n1; ++i) {
        std::vector<bool> copySkipLeft = skipLeft;
        copySkipLeft[i] = true;
        if (solve(n1, n2, edges, copySkipLeft, skipRight) < base_matching)
            resLeft[i] = 'N';
    }

    for (int j = 0; j < n2; ++j) {
        std::vector<bool> copySkipRight = skipRight;
        copySkipRight[j] = true;
        if (solve(n1, n2, edges, skipLeft, copySkipRight) < base_matching)
            resRight[j] = 'N';
    }

    std::cout << resLeft << '\n' << resRight;
    return 0;
}
