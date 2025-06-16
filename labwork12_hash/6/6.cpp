#include <iostream>
#include <vector>
#include <string>
#include <cmath>

int f1(const std::string& s) {
    long long h = 0, p = 2053, mod = 1000000007;
    for (char c : s) h = (h * p + c) % mod;
    return int(h % 3000000);
}

int f2(const std::string& s) {
    long long h = 0, p = 653, mod = 1000000007;
    for (char c : s) h = (h * p + c) % mod;
    return int(h % 3000000);
}

void push(std::string key, int n, int person, std::vector<std::pair<std::string, int>>& hash) {
    int h1 = f1(key);
    int h2 = f2(key);
    int mask = (1 << person);

    if (hash[h1].first == "" || hash[h1].first == key) {
        hash[h1].first = key;
        hash[h1].second |= mask;
    } else if (hash[h2].first == "" || hash[h2].first == key) {
        hash[h2].first = key;
        hash[h2].second |= mask;
    } else {
        std::pair<std::string, int> temp = hash[h2];
        hash[h2].first = key;
        hash[h2].second = mask;
        for (int t = 0; t < 10000; ++t) {
            int pos = f2(temp.first);
            if (hash[pos].first == "" || hash[pos].first == temp.first) {
                hash[pos] = temp;
                return;
            }
            std::swap(temp, hash[pos]);
        }
    }
}

int main() {
    int n;
    std::string name;
    std::cin >> n;
    std::vector<std::pair<std::string, int>> hash(3000000, {"", 0});

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cin >> name;
            push(name, n, i, hash);
        }
    }

    int one = 0, two = 0, three = 0;
    for (int i = 0; i < hash.size(); ++i) {
        int mask = hash[i].second;
        if (mask == 1) one += 3;
        else if (mask == 2) two += 3;
        else if (mask == 4) three += 3;
        else if (mask == 3) { one++; two++; }
        else if (mask == 5) { one++; three++; }
        else if (mask == 6) { two++; three++; }
    }
    std::cout << one << " " << two << " " << three;
    return 0;
}