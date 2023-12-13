/**
 * Project 1 ASA - 2023/2024
 * Project made by:
 * Mariana Santana (106992)
 * João Rodrigues (106221)
*/

#include <iostream>
#include <vector>
#include <stack>
#include <list>
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

/*class Graph {
public:
    int V; // Number of vertices
    std::vector<std::list<int>> adjList; // Adjacency list
    std::vector<std::list<int>> adjListT; // Transposed adjacency list

    Graph(int vertices) : V(vertices), adjList(vertices + 1), adjListT(vertices + 1) {}

    // Function to add an edge to the graph
    void addEdge(int v, int w) {
        adjList[v].push_back(w);
        adjListT[w].push_back(v);
    }

    // Iterative DFS traversal
    void iterativeDFS(int startVertex) {
        std::vector<int> visited(V + 1, 0); // Mark all vertices as not visited
        std::stack<int> stack;
        std::stack<int> stack2;
        std::list<int> descEndTime;
        // Push the startVertex onto the stack and mark it as visited
        stack.push(startVertex);

        while (!stack.empty()) {
            int currentVertex = stack.top();
            // Iterate over all adjacent vertices of the current vertex
            if (visited[currentVertex] == 0) {
                visited[currentVertex] = 1; // Mark the current vertex as visited
                //if (!adjList[currentVertex].empty()) {
                for (int neighbor : adjList[currentVertex]) { // Push the neighbor onto the stack if it hasn't been visited
                    if (visited[neighbor] == 0 || visited[neighbor] == 1) {
                        stack.push(neighbor);
                    }
                }
                //}
                else {
                    visited[currentVertex] = 2;
                    stack.pop();
                    stack.push(currentVertex + 1);
                    descEndTime.push_front(currentVertex);
                }
                printStack(stack);
            }
            else if (visited[currentVertex] == 1) {
                visited[currentVertex] = 2;
                stack.pop();
                //descEndTime.push_front(currentVertex);
                printStack(stack);
            }
            else if (visited[currentVertex] == 2) { 
                stack.pop(); 
                descEndTime.push_front(currentVertex);
                printStack(stack);
            }
            //verificar o proximo vertice a ser visitado se a stack tiver ficado vazia
        }
        printf("\ndescEndTime: \n");
        for (int i : descEndTime) {
            printf("%d ", i);
        }
    }
};*/

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
            if (currentVertex == 11) {
                printf("adjListT[11]: ");
                for (int i : adjListT[currentVertex]) {
                    printf("%d ", i);
                    bool b = visited[i];
                    printf("visited[%d]: %d\n", i, b);
                }
                printf("\n");
            }
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
    //std::vector<std::list<int>> adjList (n + 1);
    //std::vector<std::list<int>> adjListT (n + 1);

    for (int i = 0; i < m; i++) {

        int x, y;
        if (!scanf("%d %d", &x, &y)) {}

        if (0 < x && x <= n && 0 < y && y <= n) {
            //adjList[x].push_back(y);
            //adjListT[y].push_back(x);
            g.addEdge(x, y);
        }
    }
    g.findSCCs();

    return 0;
}

