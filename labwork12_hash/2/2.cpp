#include <iostream>
#include <vector>
#include <algorithm>

const long long P1 = 1009;
const long long P2 = 997;
const long long MOD1 = 1000000007;
const long long MOD2 = 1000000007;

std::vector<long long> powP1, powP2;

std::vector<long long> GetHash(const std::vector<int>& elem, int k, const std::vector<long long>& powP, long long MOD, long long P) {
    std::vector<long long> res;
    if (k > elem.size()) return res;

    long long hash = 0;
    for (int i = 0; i < k; ++i) {
        hash = (hash + powP[elem[i]]) % MOD;
    }
    res.push_back(hash);

    for (int i = k; i < elem.size(); ++i) {
        hash = (hash - powP[elem[i - k]] + MOD) % MOD;
        hash = (hash + powP[elem[i]]) % MOD;
        res.push_back(hash);
    }

    return res;
}

int main(){
    int n, m;
    std::cin >> n;
    std::vector<int> elem1(n);
    for (int i = 0; i < n; ++i){
        std::cin >> elem1[i];
    }
    std::cin >> m;
    std::vector<int> elem2(m);
    for (int i = 0; i < m; ++i){
        std::cin >> elem2[i];
    }

    int maxVal = 0;
    for (int x : elem1) maxVal = std::max(maxVal, x);
    for (int x : elem2) maxVal = std::max(maxVal, x);

    powP1.assign(maxVal + 1, 1);
    powP2.assign(maxVal + 1, 1);
    for (int i = 1; i <= maxVal; ++i) {
        powP1[i] = (powP1[i - 1] * P1) % MOD1;
        powP2[i] = (powP2[i - 1] * P2) % MOD2;
    }

    for (int k = std::min(n, m); k > 0; --k){
        std::vector<long long> hash1_1 = GetHash(elem1, k, powP1, MOD1, P1);
        std::vector<long long> hash1_2 = GetHash(elem1, k, powP2, MOD2, P2);
        std::vector<long long> hash2_1 = GetHash(elem2, k, powP1, MOD1, P1);
        std::vector<long long> hash2_2 = GetHash(elem2, k, powP2, MOD2, P2);

        std::sort(hash1_1.begin(), hash1_1.end());
        std::sort(hash1_2.begin(), hash1_2.end());

        for (size_t i = 0; i < hash2_1.size(); ++i) {
            if (std::binary_search(hash1_1.begin(), hash1_1.end(), hash2_1[i]) &&
                std::binary_search(hash1_2.begin(), hash1_2.end(), hash2_2[i])) {
                std::cout << k;
                return 0;
            }
        }
    }

    std::cout << 0;
    return 0;
}
