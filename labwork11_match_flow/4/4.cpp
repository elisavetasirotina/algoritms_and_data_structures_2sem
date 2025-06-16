#include <iostream>
#include <vector>
#include <queue>
#include <climits>

struct Edge {
    int to;
    int rev;
    int capacity;
    int flow;

    Edge(int t, int r, int c) : to(t), rev(r), capacity(c), flow(0) {}
};

std::vector<std::vector<Edge>> adj;

void addEdge(int u, int v, int c) {
    adj[u].emplace_back(v, adj[v].size(), c);
    adj[v].emplace_back(u, adj[u].size() - 1, 0);
}

int bfs(int s, int t, std::vector<int>& parent) {
    std::fill(parent.begin(), parent.end(), -1);
    std::queue<std::pair<int, int>> q;
    q.push({s, INT_MAX});

    while (!q.empty()) {
        int u = q.front().first;
        int min_flow = q.front().second;
        q.pop();

        for (Edge& e : adj[u]) {
            if (parent[e.to] == -1 && e.capacity > e.flow) {
                parent[e.to] = u;
                int new_flow = std::min(min_flow, e.capacity - e.flow);
                if (e.to == t) return new_flow;
                q.push({e.to, new_flow});
            }
        }
    }
    return 0;
}

int maxFlow(int s, int t) {
    int flow = 0;
    std::vector<int> parent(adj.size());

    while (true) {
        int pushed = bfs(s, t, parent);
        if (pushed == 0) break;

        flow += pushed;
        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            for (Edge& e : adj[u]) {
                if (e.to == v) {
                    e.flow += pushed;
                    adj[v][e.rev].flow -= pushed;
                    break;
                }
            }
        }
    }
    return flow;
}

int main() {
    int num_teams;
    std::cin >> num_teams;

    std::vector<int> current(num_teams), remain(num_teams);
    for (int& x : current) std::cin >> x;
    for (int& x : remain) std::cin >> x;

    int max_aurora = current[0] + remain[0];

    for (int i = 1; i < num_teams; ++i) {
        if (current[i] > max_aurora) {
            std::cout << "NO";
            return 0;
        }
    }

    std::vector<std::vector<int>> games(num_teams, std::vector<int>(num_teams));
    for (std::vector<int>& row : games)
        for (int& x : row)
            std::cin >> x;

    int total_games = 0;
    for (int i = 1; i < num_teams; ++i)
        for (int j = i+1; j < num_teams; ++j)
            total_games += games[i][j];

    if (total_games == 0) {
        std::cout << "YES";
        return 0;
    }

    int source = 0;
    int sink = 1 + total_games + (num_teams - 1);
    adj.resize(sink + 1);

    int match_node = 1;
    const int team_node = 1 + total_games;

    for (int i = 1; i < num_teams; ++i) {
        for (int j = i+1; j < num_teams; ++j) {
            if (games[i][j] > 0) {
                addEdge(source, match_node, games[i][j]);
                addEdge(match_node, team_node + i-1, games[i][j]);
                addEdge(match_node, team_node + j-1, games[i][j]);
                ++match_node;
            }
        }
    }

    for (int i = 1; i < num_teams; ++i) {
        int cap = max_aurora - current[i];
        if (cap < 0) {
            std::cout << "NO";
            return 0;
        }
        addEdge(team_node + i-1, sink, cap);
    }

    std::cout << (maxFlow(source, sink) == total_games ? "YES" : "NO");
    return 0;
}