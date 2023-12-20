/**
 * Project 1 ASA - 2023/2024
 * Project made by:
 * Mariana Santana (106992)
 * João Rodrigues (106221)
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>

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
                        break;
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
        void DFS2(int v, std::vector<bool>& visited, std::vector<int>& results, std::vector<int>& scc, int indexSCC) {
            // Initialize stack with starting vertex and set SCC
            std::stack<int> dfsStack, currentSCC, currentSCC2;
            dfsStack.push(v);
            visited[v] = true;
            scc[v] = indexSCC;
            int maxSCC = 0;
            bool hasNonVisitedNeighbor = false;

            while (!dfsStack.empty()) {
                int currentVertex = dfsStack.top();
                hasNonVisitedNeighbor = false;
                // Add neighbor vertices to stack if they haven't been visited
                for (int neighbor : adjListT[currentVertex]) {
                    if (!visited[neighbor]) {
                        visited[neighbor] = true;
                        hasNonVisitedNeighbor = true;
                        dfsStack.push(neighbor);
                        break;
                    }
                }
                // If all vertex's neighbors were visited, the DFS on the vertex finished
                if (!hasNonVisitedNeighbor) {
                    dfsStack.pop();
                    scc[currentVertex] = indexSCC;
                    currentSCC.push(currentVertex);
                    for (int neighbor : adjListT[currentVertex]) {
                        // Belongs to a different SCC
                        if (scc[neighbor] != scc[currentVertex] && scc[neighbor] != 0) { 
                            results[currentVertex] = std::max(results[neighbor] + 1, results[currentVertex]);
                        }
                        // Belongs to the same SCC
                        else if (scc[neighbor] == scc[currentVertex]) {
                            results[currentVertex] = std::max(results[neighbor], results[currentVertex]);
                        }
                    }
                }
            }
            // Set SCC's results to the maximum result of the SCC
            currentSCC2 = currentSCC;
            while (!currentSCC2.empty()) {
                maxSCC = maxSCC > results[currentSCC2.top()] ? maxSCC : results[currentSCC2.top()];
                currentSCC2.pop();
            }
            while (!currentSCC.empty()) {
                results[currentSCC.top()] = maxSCC;
                currentSCC.pop();
            }
        }
        // Finds SCCs with Kosaraju's algorithm and returns the longest path between SCCs
        void calcMaxSpread() {
            std::stack<int> descEndTimes;
            std::vector<bool> visited(V + 1, false);
            std::vector<int> scc(V + 1, 0);
            std::vector<int> results(V + 1, 0);
            int indexSCC = 1;
            // Set vertices in stack according to finishing times of DFS
            for (int i = 1; i <= V; i++) {
                if (!visited[i]) { DFS1(i, visited, descEndTimes); }
            }
            // Reset visited array for DFS2
            fill(visited.begin(), visited.end(), false);
            // Process vertices in order defined by the finishing times
            while (!descEndTimes.empty()) {
                int v = descEndTimes.top();
                descEndTimes.pop();
                // If the vertix hasn't been visited, it belongs to a new SCC
                if (!visited[v]) {
                    DFS2(v, visited, results, scc, indexSCC);
                    indexSCC++;
                }
            }
            // Check for the maximum result and print it
            auto max = std::max_element(results.begin(), results.end());
            printf("%d\n", *max);
        }
};

int main() {
    int n, m;
    if (!scanf("%d %d", &n, &m)) {}

    if (n < 2 || m < 0) {
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
    g.calcMaxSpread();
    return 0;
}
