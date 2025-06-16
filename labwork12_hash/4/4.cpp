#include <iostream>
#include <vector>

void push(int group, int isu, int points, std::vector<std::vector<std::pair<int, int>>>& hash){
    hash[group].push_back({isu, points});
}

void middle_score(int group, std::vector<std::vector<std::pair<int, int>>>& hash){
    int sum = 0;
    int count = 0;
    for (int i = 0; i < hash[group].size(); ++i){
        count++;
        sum += hash[group][i].second;
    }
    std::cout << sum / count  << '\n';
}

void pop(int group, int isu, std::vector<std::vector<std::pair<int, int>>>& hash){
    int i = 0;
    while(hash[group][i].first != isu){
        ++i;
    }
    hash[group][i] = hash[group].back();
    hash[group].pop_back();
}

void best(int group, std::vector<std::vector<std::pair<int, int>>>& hash){
    int best = 0;
    for (int i = 0; i < hash[group].size(); ++i){
        best = std::max(best, hash[group][i].second);
    }
    std::cout << best << '\n';
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int M, Q;
    std::cin >> M >> Q;
    char symbol;
    int group, isu, points;
    std::vector<std::vector<std::pair<int, int>>> hash(M);
    for (int i = 0; i < Q; ++i){
        std::cin >> symbol >> group;
        if (symbol == 'a'){
            middle_score(group - 1, hash);
        }
        if (symbol == '-'){
            std:: cin >> isu;
            pop(group - 1, isu, hash);
        }
        if (symbol == '+'){
            std:: cin >> isu >> points;
            push(group - 1, isu, points, hash);
        }
        if (symbol == 'm'){
            best(group - 1, hash);
        }
    }
    return 0;
}
