#include <iostream>
#include <cassert>
#include <random>
#include <chrono>
#include "dcp.h"
#include "naive_dcp.h"
#include "../include/random_generators.hpp"

void test_dcp_basic() {
    std::vector<Query> queries = {
        {0, 0, 1, -1},  // Add edge (0, 1)
        {2, 0, 1, 0},   // Get connectivity of (0, 1)
        {1, 0, 1, -1},  // Remove edge (0, 1)
        {2, 0, 1, 1}    // Get connectivity of (0, 1)
    };
    
    std::vector<int> result = solve(queries, 2);
    assert(result.size() == 2);
    assert(result[0] == 1);  // (0, 1) should be connected
    assert(result[1] == 0);  // (0, 1) should not be connected
    std::cout << "Basic DCP test passed." << std::endl;
}

void test_naive_dcp_basic() {
    std::vector<Query> queries = {
        {0, 0, 1, -1},  // Add edge (0, 1)
        {2, 0, 1, 0},   // Get connectivity of (0, 1)
        {1, 0, 1, -1},  // Remove edge (0, 1)
        {2, 0, 1, 1}    // Get connectivity of (0, 1)
    };
    
    std::vector<int> result = solve_naive(queries, 2);
    assert(result.size() == 2);
    assert(result[0] == 1);  // (0, 1) should be connected
    assert(result[1] == 0);  // (0, 1) should not be connected
    std::cout << "Basic Naive DCP test passed." << std::endl;
}

void stress_test(int n, int operations) {
    RandomGenerators gen;
    std::vector<Query> queries;

    for (int i = 0; i < operations; i++) {
        int type = gen.generateIntegerSequence(1, 0, 2)[0];
        int u = gen.generateIntegerSequence(1, 0, n-1)[0];
        int v = gen.generateIntegerSequence(1, 0, n-1)[0];
        while (v == u) v = gen.generateIntegerSequence(1, 0, n-1)[0];
        queries.push_back({type, u, v, i});
    }

    std::vector<int> naive_result = solve_naive(queries, n);
    std::vector<int> optimized_result = solve(queries, n);
    if (naive_result != optimized_result) {
        std::cerr << "Stress test failed for n = " << n << " and " << operations << " operations." << std::endl;
        for (const auto& q : queries) {
            std::cerr << q.type << ' ' << q.u << ' ' << q.v << ' ' << q.index << '\n';
        }
        std::cerr << "Naive result: ";
        for (int x : naive_result) std::cerr << x << ' ';
        std::cerr << "\nOptimized result: ";
        for (int x : optimized_result) std::cerr << x << ' ';
        std::cerr << '\n';
    }
    assert(naive_result == optimized_result);
    std::cout << "Stress test passed for n = " << n << " and " << operations << " operations." << std::endl;
}

void performance_test(int n, int operations) {
    RandomGenerators gen;
    std::vector<Query> queries;

    for (int i = 0; i < operations; i++) {
        int type = gen.generateIntegerSequence(1, 0, 2)[0];
        int u = gen.generateIntegerSequence(1, 0, n-1)[0];
        int v = gen.generateIntegerSequence(1, 0, n-1)[0];
        while (v == u) v = gen.generateIntegerSequence(1, 0, n-1)[0];
        queries.push_back({type, u, v, i});
    }

    auto start_naive = std::chrono::high_resolution_clock::now();
    std::vector<int> naive_result = solve_naive(queries, n);
    auto end_naive = std::chrono::high_resolution_clock::now();

    auto start_optimized = std::chrono::high_resolution_clock::now();
    std::vector<int> optimized_result = solve(queries, n);
    auto end_optimized = std::chrono::high_resolution_clock::now();

    auto naive_duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_naive - start_naive);
    auto optimized_duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_optimized - start_optimized);

    std::cout << "Performance test for n = " << n << " and " << operations << " operations:" << std::endl;
    std::cout << "Naive DCP time: " << naive_duration.count() << " ms" << std::endl;
    std::cout << "Optimized DCP time: " << optimized_duration.count() << " ms" << std::endl;
}


void test_dcp_disconnected_components() {
    const int N = 10;
    std::vector<Query> queries = {
        {0, 0, 1, -1},  // Connect 0-1
        {0, 2, 3, -1},  // Connect 2-3
        {0, 4, 5, -1},  // Connect 4-5
        {2, 0, 1, 0},   // Check 0-1
        {2, 0, 2, 1},   // Check 0-2
        {2, 2, 3, 2},   // Check 2-3
        {2, 4, 5, 3},   // Check 4-5
        {2, 3, 5, 4}    // Check 3-5
    };
    
    std::vector<int> result = solve(queries, N);
    assert(result.size() == 5);
    assert(result[0] == 1);  // 0-1 connected
    assert(result[1] == 0);  // 0-2 not connected
    assert(result[2] == 1);  // 2-3 connected
    assert(result[3] == 1);  // 4-5 connected
    assert(result[4] == 0);  // 3-5 not connected
    std::cout << "Disconnected components DCP test passed." << std::endl;
}

void test_dcp_edge_removal() {
    const int N = 5;
    std::vector<Query> queries = {
        {0, 0, 1, -1},  // Add edge 0-1
        {0, 1, 2, -1},  // Add edge 1-2
        {0, 2, 3, -1},  // Add edge 2-3
        {0, 3, 4, -1},  // Add edge 3-4
        {2, 0, 4, 0},   // Check 0-4
        {1, 2, 3, -1},  // Remove edge 2-3
        {2, 0, 4, 1},   // Check 0-4 again
        {2, 0, 2, 2},   // Check 0-2
        {2, 3, 4, 3}    // Check 3-4
    };
    
    std::vector<int> result = solve(queries, N);
    assert(result.size() == 4);
    assert(result[0] == 1);  // 0-4 initially connected
    assert(result[1] == 0);  // 0-4 disconnected after removal
    assert(result[2] == 1);  // 0-2 still connected
    assert(result[3] == 1);  // 3-4 still connected
    std::cout << "Edge removal DCP test passed." << std::endl;
}

void test_dcp_cyclic_graph() {
    const int N = 6;
    std::vector<Query> queries = {
        {0, 0, 1, -1},  // Add edge 0-1
        {0, 1, 2, -1},  // Add edge 1-2
        {0, 2, 3, -1},  // Add edge 2-3
        {0, 3, 4, -1},  // Add edge 3-4
        {0, 4, 5, -1},  // Add edge 4-5
        {0, 5, 0, -1},  // Add edge 5-0 (creating a cycle)
        {2, 0, 3, 0},   // Check 0-3
        {1, 2, 3, -1},  // Remove edge 2-3
        {2, 0, 3, 1},   // Check 0-3 again
        {1, 0, 1, -1},  // Remove edge 0-1
        {1, 5, 0, -1},  // Remove edge 5-0
        {2, 0, 3, 2}    // Check 0-3 once more
    };
    
    std::vector<int> result = solve(queries, N);
    assert(result.size() == 3);
    assert(result[0] == 1);  // 0-3 initially connected
    assert(result[1] == 1);  // 0-3 still connected after removing one edge
    assert(result[2] == 0);  // 0-3 disconnected after removing two more edges
    std::cout << "Cyclic graph DCP test passed." << std::endl;
}

int main() {
    test_dcp_basic();
    test_naive_dcp_basic();
    test_dcp_disconnected_components();
    test_dcp_edge_removal();
    test_dcp_cyclic_graph();
    
    stress_test(5, 10);
    stress_test(10, 100);
    stress_test(100, 1000);
    stress_test(1000, 10000);
    
    performance_test(5000, 10000);

    std::cout << "All tests passed!" << std::endl;
    return 0;
}
