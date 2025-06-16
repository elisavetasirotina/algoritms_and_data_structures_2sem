#include <iostream>
#include <vector>

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    long long count = 0;
    std::cin >> n;

    std::vector<int> s(n);
    std::vector<long long> diff(10100003, 0);

    for (int i = 0; i < n; ++i){
        std::cin >> s[i];
        int key = (s[i] - i) + 10000001;
        diff[key]++;
    }

    for (int i = 0; i < diff.size(); ++i){
        count += diff[i] * (diff[i] - 1) / 2;
    }

    std::cout << count;
    return 0;
}
