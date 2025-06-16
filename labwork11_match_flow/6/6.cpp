#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>

struct Edge {
    int to, rev, capacity, flow;
    Edge(int to, int rev, int capacity) : to(to), rev(rev), capacity(capacity), flow(0) {}
};

std::vector<std::vector<Edge>> adj;
int total_profit = 0;
int total_discount_benefit = 0;

void addEdge(int u, int v, int capacity) {
    adj[u].emplace_back(v, adj[v].size(), capacity);
    adj[v].emplace_back(u, adj[u].size() - 1, 0);
}

int bfs(int s, int t, std::vector<int>& parent) {
    std::fill(parent.begin(), parent.end(), -1);
    std::queue<std::pair<int, int>> q;
    q.push({s, INT_MAX});
    parent[s] = -2;

    while (!q.empty()) {
        int u = q.front().first;
        int flow = q.front().second;
        q.pop();

        for (Edge& e : adj[u]) {
            if (parent[e.to] == -1 && e.capacity > e.flow) {
                parent[e.to] = u;
                int new_flow = std::min(flow, e.capacity - e.flow);
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
    int N, M, P;
    std::cin >> N >> M >> P;

    int source = 0;
    int sink = 1;
    int delivery_offset = 2;
    int module_offset = delivery_offset + N;
    int discount_offset = module_offset + M;

    adj.resize(discount_offset + P + 2);

    std::vector<std::vector<int>> delivery_modules(N);
    std::vector<int> module_cost(M);
    std::vector<std::pair<int, int>> discounts(P);
    std::vector<int> discount_cost(P);
    for (int i = 0; i < N; ++i) {
        int V, K;
        std::cin >> V >> K;
        total_profit += V;
        addEdge(source, delivery_offset + i, V);

        delivery_modules[i].resize(K);
        for (int j = 0; j < K; ++j) {
            int mod;
            std::cin >> mod;
            --mod;
            delivery_modules[i][j] = mod;
        }
    }

    for (int i = 0; i < M; ++i) {
        std::cin >> module_cost[i];
        addEdge(module_offset + i, sink, module_cost[i]);
    }

    for (int i = 0; i < P; ++i) {
        int a, b, d;
        std::cin >> a >> b >> d;
        --a;
        --b;
        int cost_a = module_cost[a];
        int cost_b = module_cost[b];
        int benefit = (cost_a + cost_b) - d;

        if (benefit > 0) {
            total_discount_benefit += benefit;
            addEdge(source, discount_offset + i, benefit);
            addEdge(discount_offset + i, module_offset + a, INT_MAX);
            addEdge(discount_offset + i, module_offset + b, INT_MAX);
        }
        discounts[i] = {a, b};
        discount_cost[i] = d;
    }

    for (int i = 0; i < N; ++i) {
        int delivery_node = delivery_offset + i;
        for (int mod : delivery_modules[i]) {
            addEdge(delivery_node, module_offset + mod, INT_MAX);
        }
    }

    int min_cost = maxFlow(source, sink);
    int answer = total_profit + total_discount_benefit - min_cost;
    std::cout << answer;

    return 0;
}