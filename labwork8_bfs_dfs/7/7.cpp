#include <iostream>
#include <queue>
#include <vector>

struct Coordinates {
    int x;
    int y;
    int z;
    Coordinates(int input_x, int input_y, int input_z) {
        x = input_x;
        y = input_y;
        z = input_z;
    }
};

class Graph {
public:
    int V;
    std::vector<std::vector<Coordinates>> list_of_adjacency;
    int ***distance;
    bool ***visited;
    bool ***plants;

    Graph() : V(102 * 102 * 201), list_of_adjacency(V + 1) {
        distance = new int**[102];
        visited = new bool**[102];
        plants = new bool**[102];

        for (int i = 0; i < 102; ++i) {
            distance[i] = new int*[102];
            visited[i] = new bool*[102];
            plants[i] = new bool*[102];

            for (int j = 0; j < 102; ++j) {
                distance[i][j] = new int[201];
                visited[i][j] = new bool[201];
                plants[i][j] = new bool[201];

                for (int k = 0; k < 201; ++k) {
                    visited[i][j][k] = false;
                    distance[i][j][k] = 1000000 + 1;
                    plants[i][j][k] = false;
                }
            }
        }
    }

    void addEdge(int v, Coordinates edge) {
        list_of_adjacency[v].push_back(edge);
    }

    void BFS(Coordinates start) {
        std::queue<Coordinates> queue;
        queue.push(start);
        visited[start.x][start.y][start.z] = true;
        distance[start.x][start.y][start.z] = 0;

        while (!queue.empty()) {
            Coordinates current = queue.front();
            queue.pop();

            int index = current.x * 102 * 201 + current.y * 201 + current.z;

            for (int i = 0; i < (int)list_of_adjacency[index].size(); i++) {
                Coordinates neighbor = list_of_adjacency[index][i];
                if (!visited[neighbor.x][neighbor.y][neighbor.z]) {
                    visited[neighbor.x][neighbor.y][neighbor.z] = true;
                    distance[neighbor.x][neighbor.y][neighbor.z] = distance[current.x][current.y][current.z] + 1;
                    queue.push(neighbor);
                }
            }
        }
    }
};

int main() {
    int K, E, xs, ys, zs, xf, yf, zf, x, y, z, h;
    std::cin >> K >> E >> xs >> ys >> zs >> xf >> yf >> zf;
    Graph g;

    for (int i = 0; i < K; ++i) {
        std::cin >> x >> y >> z >> h;
        for (int k = 0; k < h; ++k) {
            g.plants[x][y][z + k] = true;
        }
    }

    if (xs == xf && ys == yf && zs == zf) {
        std::cout << 0;
        return 0;
    }

    for (int x = 1; x < 101; ++x) {
        for (int y = 1; y < 101; ++y) {
            for (int z = 1; z < 200; ++z) {
                if (!g.plants[x][y][z]) {
                    int index = x * 102 * 201 + y * 201 + z;
                    if (!g.plants[x + 1][y][z]) {
                        g.addEdge(index, Coordinates(x + 1, y, z));
                    }
                    if (!g.plants[x][y + 1][z]) {
                        g.addEdge(index, Coordinates(x, y + 1, z));
                    }
                    if (!g.plants[x][y][z + 1]) {
                        g.addEdge(index, Coordinates(x, y, z + 1));
                    }
                    if (!g.plants[x - 1][y][z]) {
                        g.addEdge(index, Coordinates(x - 1, y, z));
                    }
                    if (!g.plants[x][y - 1][z]) {
                        g.addEdge(index, Coordinates(x, y - 1, z));
                    }
                    if (!g.plants[x][y][z - 1]) {
                        g.addEdge(index, Coordinates(x, y, z - 1));
                    }
                }
            }
        }
    }

    g.BFS(Coordinates(xs, ys, zs));

    if (g.distance[xf][yf][zf] > E || g.distance[xf][yf][zf] == 1000000 + 1) {
        std::cout << -1;
    } else {
        std::cout << g.distance[xf][yf][zf];
    }

    return 0;
}
