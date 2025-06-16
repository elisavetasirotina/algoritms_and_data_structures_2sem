#include <iostream>
#include <vector>

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, value;
    std::cin >> n;
    int mod = n * 2;
    std::vector<std::vector<int>> hash(mod);

    for (int i = 0; i < n; ++i){
        std::cin >> value;
        int idx = value % mod;
        if (idx < 0) idx += mod;
        hash[idx].push_back(value);
    }

    for (int i = 0; i < n; ++i){
        std::cin >> value;
        int idx = value % mod;
        if (idx < 0) idx += mod;
        bool flag = false;
        for (int j = 0; j < (int)hash[idx].size(); ++j){
            if (hash[idx][j] == value){
                hash[idx][j] = hash[idx].back();
                hash[idx].pop_back();
                flag = true;
                break;
            }
        }
        if (!flag){
            std::cout << "NO";
            return 0;
        }
    }
    std::cout << "YES";
    return 0;
}
