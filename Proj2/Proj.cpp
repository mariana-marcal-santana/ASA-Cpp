/**
 * Project 1 ASA - 2023/2024
 * Project made by:
 * Mariana Santana (106992)
 * João Rodrigues (106221)
*/

#include <iostream>
#include <vector>
#include <stack>
#include <limits>

void printStack(std::stack<int> stack) {
    printf("Stack:");
    std::stack<int> stack2 = stack;
    while (!stack2.empty()) {
        printf("%d ", stack2.top());
        stack2.pop();
    }
    printf("\n");
}

class Graph {
public:
    int V; // Number of vertices
    std::vector<std::vector<int>> adjList; // Adjacency list
    std::vector<std::vector<int>> adjListT; // Transposed adjacency list

    Graph(int vertices) : V(vertices), adjList(vertices + 1), adjListT(vertices + 1) {}

    // Function to add an edge to the graph
    void addEdge(int v, int w) {
        adjList[v].push_back(w);
        adjListT[w].push_back(v);
    }

    // Function to perform DFS and fill the stack with vertices in order of finishing time
    void fillOrder(int v, std::vector<bool>& visited, std::stack<int>& stack) {
        visited[v] = true;
        // Use an explicit stack to simulate recursion
        std::stack<int> dfsStack;
        dfsStack.push(v);

        while (!dfsStack.empty()) {
            int currentVertex = dfsStack.top();
            bool hasNonVisitedNeighbor = false;

            for (int neighbor : adjList[currentVertex]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    hasNonVisitedNeighbor = true;
                    dfsStack.push(neighbor);
                }
            }
            if (!hasNonVisitedNeighbor) {
                dfsStack.pop();
                stack.push(currentVertex);
            }
        }
    }

    // Function to perform DFS starting from a given vertex
    void DFS(int v, std::vector<bool>& visited, std::vector<int>& scc, int indexSCC) {
        visited[v] = true;
        scc[v] = indexSCC;
        // Use an explicit stack to simulate recursion
        std::stack<int> dfsStack;
        dfsStack.push(v);

        while (!dfsStack.empty()) {
            int currentVertex = dfsStack.top();
            dfsStack.pop();
            for (int neighbor : adjListT[currentVertex]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    scc[neighbor] = indexSCC;
                    dfsStack.push(neighbor);
                }
            }
        }
    }

    // Function to find Strongly Connected Components using Kosaraju's algorithm
    void findSCCs() {
        std::stack<int> stack;
        std::vector<bool> visited(V + 1, false);
        std::vector<int> scc(V + 1, 0);
        int indexSCC = 1;

        // Fill vertices in stack according to finishing times
        for (int i = 1; i < V; i++) {
            if (!visited[i]) { fillOrder(i, visited, stack); }
        }

        printStack(stack);

        // Reset visited array for the second DFS
        fill(visited.begin(), visited.end(), false);

        // Process vertices in order defined by the finishing times
        while (!stack.empty()) {
            int v = stack.top();
            stack.pop();

            if (!visited[v]) {
                DFS(v, visited, scc, indexSCC);
                indexSCC++;
            }
        }
        printf("SCC: ");
        for (int i = 1; i <= V; i++) {
            printf("%d ", scc[i]);
        }
        printf("\n");
    }
};

int main() {
    int n, m;
    if (!scanf("%d %d", &n, &m)) {}

    if (n < 2 || m < 1) {
        printf("0\n");
        return 0;
    }

    Graph g(n);

    for (int i = 0; i < m; i++) {

        int x, y;
        if (!scanf("%d %d", &x, &y)) {}

        if (0 < x && x <= n && 0 < y && y <= n) {
            g.addEdge(x, y);
        }
    }
    g.findSCCs();

    return 0;
}

