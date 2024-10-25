#ifndef RANDOM_GENERATORS_HPP
#define RANDOM_GENERATORS_HPP

#include <vector>
#include <random>
#include <algorithm>
#include <chrono>

class RandomGenerators {
private:
    std::mt19937 rng;

public:
    RandomGenerators() : rng(std::chrono::steady_clock::now().time_since_epoch().count()) {}

    // Generate a random integer sequence
    std::vector<int> generateIntegerSequence(int size, int min_value, int max_value) {
        std::vector<int> sequence(size);
        std::uniform_int_distribution<int> dist(min_value, max_value);
        for (int& num : sequence) {
            num = dist(rng);
        }
        return sequence;
    }

    // Generate a random graph (adjacency list representation)
    std::vector<std::vector<int>> generateGraph(int num_vertices, int num_edges) {
        std::vector<std::vector<int>> graph(num_vertices);
        std::uniform_int_distribution<int> vertex_dist(0, num_vertices - 1);

        for (int i = 0; i < num_edges; ++i) {
            int u = vertex_dist(rng);
            int v = vertex_dist(rng);
            if (u != v && std::find(graph[u].begin(), graph[u].end(), v) == graph[u].end()) {
                graph[u].push_back(v);
                graph[v].push_back(u);
            }
        }
        return graph;
    }

    // Generate a random rooted tree
    std::vector<int> generateRootedTree(int num_vertices) {
        std::vector<int> parent(num_vertices, -1);
        for (int i = 1; i < num_vertices; ++i) {
            std::uniform_int_distribution<int> dist(0, i - 1);
            parent[i] = dist(rng);
        }
        return parent;
    }

    // Generate a random permutation
    std::vector<int> generatePermutation(int size) {
        std::vector<int> perm(size);
        for (int i = 0; i < size; ++i) {
            perm[i] = i;
        }
        std::shuffle(perm.begin(), perm.end(), rng);
        return perm;
    }
};

#endif // RANDOM_GENERATORS_HPP
