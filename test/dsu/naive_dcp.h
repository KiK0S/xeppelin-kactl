#include <vector>
#include <algorithm>
#include <iostream>
#include "dcp.h"

class NaiveDCP {
private:
    int N; // number of nodes
    std::vector<std::vector<int>> graph;
    std::vector<bool> visited;

    void dfs(int node) {
        visited[node] = true;
        for (int neighbor : graph[node]) {
            if (!visited[neighbor]) {
                dfs(neighbor);
            }
        }
    }

public:
    NaiveDCP(int n) : N(n), graph(n), visited(n) {}

    void addEdge(int u, int v) {
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    void removeEdge(int u, int v) {
        graph[u].erase(std::remove(graph[u].begin(), graph[u].end(), v), graph[u].end());
        graph[v].erase(std::remove(graph[v].begin(), graph[v].end(), u), graph[v].end());
    }

    bool isConnected(int u, int v) {
        std::fill(visited.begin(), visited.end(), false);
        dfs(u);
        return visited[v];
    }

    std::vector<int> solve(const std::vector<Query>& queries) {
        std::vector<int> results;
        for (const auto& query : queries) {
            if (query.type == 0) {
                addEdge(query.u, query.v);
            } else if (query.type == 1) {
                removeEdge(query.u, query.v);
            } else if (query.type == 2) {
                results.push_back(isConnected(query.u, query.v));
            }
        }
        return results;
    }
};

std::vector<int> solve_naive(const std::vector<Query>& queries, int N) {
    NaiveDCP solver(N);
    return solver.solve(queries);
}