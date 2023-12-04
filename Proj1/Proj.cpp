/**
 * Project 1 ASA - 2023/2024
 * Project made by:
 * Mariana Santana (106992)
 * João Rodrigues (106221)
*/

#include <iostream>
#include <vector>

int calcMaxPrice(std::vector<std::vector<int>>& m, int X, int Y) {
    for (int i = 0; i < X; i++) {
        for (int j = 0; j < Y; j++) {
            for (int k = 0; k < i; k++) {
                m[i][j] = std::max(m[i][j], m[k][j] + m[i - k - 1][j]);
            }
            for (int k = 0; k < j; k++) {
                m[i][j] = std::max(m[i][j], m[i][k] + m[i][j - k - 1]);
            }
        }
    }
    return m[X - 1][Y - 1];
}

int main() {

    int X, Y, n;
    
    if (!scanf("%d %d", &X, &Y));
    if (!scanf("%d", &n));
    
    std::vector<std::vector<int>> m(X, std::vector<int>(Y, 0));

    if (X <= 0 || Y <= 0 || n <= 0) {
        printf("0\n");
        return 0;
    }

    for (int i = 0; i < n; i++) {

        int a, b, p;
        if (!scanf("%d %d %d", &a, &b, &p));

        if (a > 0 && b > 0 && p > 0) {
            if (a <= X && b <= Y) {
                m[a-1][b-1] = std::max(m[a-1][b-1], p);
            }
            if (a <= Y && b <= X) {
                m[b-1][a-1] = std::max(m[b-1][a-1], p);
            }
        }
    }
    printf("%d\n", calcMaxPrice(m, X, Y));
    return 0;
}