#include <iostream>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, x, y, count = 0;
    std::cin >> n;

    std::vector<std::pair<int, int>> hash_x(2 * n, {-1, 0});
    std::vector<std::pair<int, int>> hash_y(2 * n, {-1, 0});

    for (int i = 0; i < n; ++i) {
        std::cin >> x >> y;

        int index_x = (x) % (2 * n);
        while (hash_x[index_x].first != -1 && hash_x[index_x].first != x) {
            index_x = (index_x + 1) % (2 * n);
        }
        hash_x[index_x].first = x;
        hash_x[index_x].second++;

        int index_y = (y) % (2 * n);
        while (hash_y[index_y].first != -1 && hash_y[index_y].first != y) {
            index_y = (index_y + 1) % (2 * n);
        }
        hash_y[index_y].first = y;
        hash_y[index_y].second++;
    }

    for (int k = 0; k < 3; ++k) {
        int max_count = 0;
        int max_index = -1;
        bool is_x = true;

        for (int i = 0; i < 2 * n; ++i) {
            if (hash_x[i].first != -1 && hash_x[i].second > max_count) {
                max_count = hash_x[i].second;
                max_index = i;
                is_x = true;
            }
        }

        for (int i = 0; i < 2 * n; ++i) {
            if (hash_y[i].first != -1 && hash_y[i].second > max_count) {
                max_count = hash_y[i].second;
                max_index = i;
                is_x = false;
            }
        }

        count += max_count;

        if (max_index == -1) break;

        if (is_x) {
            int key = hash_x[max_index].first;
            hash_x[max_index] = {-1, 0};
            for (int i = 0; i < 2 * n; ++i) {
                if (hash_y[i].first != -1) {
                    if (hash_y[i].first == key) {
                        hash_y[i] = {-1, 0};
                    }
                }
            }
        } else {
            int key = hash_y[max_index].first;
            hash_y[max_index] = {-1, 0};
            for (int i = 0; i < 2 * n; ++i) {
                if (hash_x[i].first != -1) {
                    if (hash_x[i].first == key) {
                        hash_x[i] = {-1, 0};
                    }
                }
            }
        }
    }

    if (count >= n) {
        std::cout << "YES";
    } else {
        std::cout << "NO";
    }

    return 0;
}
