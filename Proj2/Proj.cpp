/**
 * Project 1 ASA - 2023/2024
 * Project made by:
 * Mariana Santana (106992)
 * João Rodrigues (106221)
*/

#include <iostream>
#include <vector>

int calcMaxSpread(std::vector<std::vector<int>>& matrix) {
    return 0;
}

int main() {

    int n, m;
    if (!scanf("%d %d", &n, &m)) {}

    if (n < 2 || m < 1) {
        printf("0\n");
        return 0;
    }
    
    std::vector<std::vector<int>> adjList(n, std::vector<int>(n, 0));
    //std::vector<std::vector<

    for (int i = 0; i < m; i++) {

        int x, y;
        if (!scanf("%d %d", &x, &y)) {}

        if (0 < x && x <= n && 0 < y && y <= n) {
            adjList[x - 1][y - 1] = 1;
        }
    }

    for (int i = 0; i < n; i++) {
        //printf("%d: ", i);
        for (int j = 0; j < n; j++) {
            printf("%d ", adjList[i][j]);
        }
        printf("\n");
    }

    printf("%d\n", calcMaxSpread(adjList));
    return 0;
}