#include <iostream>
#include <vector>
#include <queue>
#include <omp.h>
using namespace std;

vector<int> graph[100];
bool visited[100];
int n;

void addEdge(int u, int v) {
    graph[u].push_back(v);
    graph[v].push_back(u);
}

void parallelBFS(int start) {
    queue<int> q;
    q.push(start);
    visited[start] = true;

    while (!q.empty()) {
        int node = q.front();
        q.pop();
        cout << "BFS Visited: " << node << endl;

        #pragma omp parallel for
        for (int i = 0; i < graph[node].size(); i++) {
            int neighbor = graph[node][i];
            if (!visited[neighbor]) {
                #pragma omp critical
                {
                    if (!visited[neighbor]) {
                        visited[neighbor] = true;
                        q.push(neighbor);
                    }
                }
            }
        }
    }
}

void parallelDFS(int node) {
    visited[node] = true;
    cout << "DFS Visited: " << node << endl;

    #pragma omp parallel for
    for (int i = 0; i < graph[node].size(); i++) {
        int neighbor = graph[node][i];
        if (!visited[neighbor]) {
            parallelDFS(neighbor);
        }
    }
}

int main() {
    n = 6;
    addEdge(0,1);
    addEdge(0,2);
    addEdge(1,3);
    addEdge(1,4);
    addEdge(2,5);

    cout << "--- Parallel BFS ---" << endl;
    fill(visited, visited+n, false);
    parallelBFS(0);

    cout << "\n--- Parallel DFS ---" << endl;
    fill(visited, visited+n, false);
    parallelDFS(0);

    return 0;
}
