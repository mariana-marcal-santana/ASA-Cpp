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
        // Add edge to adjacency list and its transposed to the transposed adjacency list
        void addEdge(int v, int w) {
            adjList[v].push_back(w);
            adjListT[w].push_back(v);
        }
        // DFS and fill the stack with vertices in order of finishing time
        void DFS1(int v, std::vector<bool>& visited, std::stack<int>& descendingEndTimes) {
            // Initialize stack with starting vertex
            std::stack<int> dfsStack;
            dfsStack.push(v);
            visited[v] = true;

            while (!dfsStack.empty()) {
                int currentVertex = dfsStack.top();
                bool hasNonVisitedNeighbor = false;
                // Add neighbor vertices to stack if they haven't been visited
                for (int neighbor : adjList[currentVertex]) {
                    if (!visited[neighbor]) {
                        visited[neighbor] = true;
                        hasNonVisitedNeighbor = true;
                        dfsStack.push(neighbor);
                    }
                }
                // If all vertex's neighbors were visited, the DFS on the vertex finished
                if (!hasNonVisitedNeighbor) {
                    dfsStack.pop();
                    // Add vertex to stack in order of finishing time
                    descendingEndTimes.push(currentVertex);
                }
            }
        }
        // Find and set SCCs on a vector with DFS of transposed graph
        void DFS2(int v, std::vector<bool>& visited, std::vector<int>& scc, int indexSCC) {
            // Initialize stack with starting vertex and set SCC
            std::stack<int> dfsStack;
            dfsStack.push(v);
            visited[v] = true;
            scc[v] = indexSCC;
            
            while (!dfsStack.empty()) {
                int currentVertex = dfsStack.top();
                dfsStack.pop();
                for (int neighbor : adjListT[currentVertex]) {
                    if (!visited[neighbor]) {
                        visited[neighbor] = true;
                        // Set neighbor as part of the same SCC
                        scc[neighbor] = indexSCC;
                        dfsStack.push(neighbor);
                    }
                }
            }
        }

        // Function to find SCCs with Kosaraju's algorithm
        void findSCCs() {

            std::stack<int> descendingEndTimes;
            std::vector<bool> visited(V + 1, false);
            std::vector<int> scc(V + 1, 0);
            int indexSCC = 1;

            // Set vertices in stack according to finishing times of DFS
            for (int i = 1; i < V; i++) {
                if (!visited[i]) { DFS1(i, visited, descendingEndTimes); }
            }
            printStack(descendingEndTimes);
            // Reset visited array for DFS2
            fill(visited.begin(), visited.end(), false);
            // Process vertices in order defined by the finishing times
            while (!descendingEndTimes.empty()) {
                int v = descendingEndTimes.top();
                descendingEndTimes.pop();
                // If the vertix hasn't been visited, it belongs to a new SCC
                if (!visited[v]) {
                    DFS2(v, visited, scc, indexSCC);
                    indexSCC++;
                }
            }
            printf("SCC: ");
            for (int i = 1; i <= V; i++) { printf("%d ", scc[i]); }
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

