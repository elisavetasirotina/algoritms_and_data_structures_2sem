#include <iostream>
#include <queue>
#include <climits>

int main() {
    long long h;
    int a, b, c;
    std::cin >> h >> a >> b >> c;

    int min_abc = std::min(a, std::min(b, c));
    long long* reachable = new long long[min_abc];
    for (int i = 0; i < min_abc; ++i){
        reachable[i] = LLONG_MAX;
    }

    std::queue<long long> q;
    q.push(1);
    reachable[1 % min_abc] = 1;

    while (!q.empty()) {
        long long curr_height = q.front();
        q.pop();

        if (curr_height + a <= h && (reachable[(curr_height + a) % min_abc] > (curr_height + a))){
            reachable[(curr_height + a) % min_abc] = curr_height + a;
            q.push(curr_height + a);
        }
        if (curr_height + b <= h && (reachable[(curr_height + b) % min_abc] > (curr_height + b))) {
            reachable[(curr_height + b) % min_abc] = curr_height + b;
            q.push(curr_height + b);
        }
        if (curr_height + c <= h && (reachable[(curr_height + c) % min_abc] > (curr_height + c))){
            reachable[(curr_height + c) % min_abc] = curr_height + c;
            q.push(curr_height + c);
        }
    }

    long long count = 0;
    for (int i = 0; i < min_abc; ++i) {
        if (reachable[i] != LONG_MAX) {
            count += (h - reachable[i]) / min_abc + 1;
        }
    }

    std::cout << count;
    return 0;
}