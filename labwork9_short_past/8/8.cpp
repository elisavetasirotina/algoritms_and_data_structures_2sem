#include <iostream>
int main(){
    int v, e;
    std::cin >> v >> e;
    int** matrix = new int*[v + 1];
    for (int i = 0; i < v; ++i){
        matrix[i] = new int[v + 1]{-1};
    }
    for(int i = 1; i <= v; ++i){
        for(int j = i; j <= v; ++j){
            if (i != j){
                if (i == 1) {
                    matrix[i][j] = matrix[i][j - 1] + 1;
                } else{
                    matrix[i][j] = matrix[1][j] - 1 - matrix[1][i];
                }
                std:: cout << i << " " << j << " " << matrix[i][j] << '\n';
                e--;
                if (e == 0){
                    return 0;
                }
            }
        }
    }
    return 0;
}