#include <iostream>
#include <cassert>
#include <random>
#include <chrono>
#include "dsu.h"
#include "naive_dsu.h"
#include "../include/random_generators.hpp"

void test_dsu_basic() {
    DSU dsu(5);
    assert(dsu.get(0) == 0);
    assert(dsu.get(1) == 1);
    dsu.unite(0, 1);
    assert(dsu.get(0) == dsu.get(1));
    dsu.unite(2, 3);
    assert(dsu.get(2) == dsu.get(3));
    assert(dsu.get(0) != dsu.get(2));
    dsu.unite(0, 2);
    assert(dsu.get(0) == dsu.get(2));
    std::cout << "Basic DSU test passed." << std::endl;
}

void test_naive_dsu_basic() {
    NaiveDSU naive_dsu(5);
    assert(naive_dsu.get(0) == 0);
    assert(naive_dsu.get(1) == 1);
    naive_dsu.unite(0, 1);
    assert(naive_dsu.get(0) == naive_dsu.get(1));
    naive_dsu.unite(2, 3);
    assert(naive_dsu.get(2) == naive_dsu.get(3));
    assert(naive_dsu.get(0) != naive_dsu.get(2));
    naive_dsu.unite(0, 2);
    assert(naive_dsu.get(0) == naive_dsu.get(2));
    std::cout << "Basic Naive DSU test passed." << std::endl;
}

void stress_test(int n, int operations) {
    RandomGenerators gen;
    DSU dsu(n);
    NaiveDSU naive_dsu(n);

    for (int i = 0; i < operations; i++) {
        int op = gen.generateIntegerSequence(1, 0, 1)[0];
        int a = gen.generateIntegerSequence(1, 0, n-1)[0];
        int b = gen.generateIntegerSequence(1, 0, n-1)[0];

        if (op == 0) {  // get operation
            assert(dsu.get(a) == dsu.get(b) == (naive_dsu.get(a) == naive_dsu.get(b)));
        } else {  // unite operation
            dsu.unite(a, b);
            naive_dsu.unite(a, b);
        }
    }
    std::cout << "Stress test passed for n = " << n << " and " << operations << " operations." << std::endl;
}

void performance_test(int n, int operations) {
    RandomGenerators gen;
    DSU dsu(n);
    NaiveDSU naive_dsu(n);

    auto start_dsu = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < operations; i++) {
        int op = gen.generateIntegerSequence(1, 0, 1)[0];
        int a = gen.generateIntegerSequence(1, 0, n-1)[0];
        int b = gen.generateIntegerSequence(1, 0, n-1)[0];

        if (op == 0) {
            dsu.get(a);
        } else {
            dsu.unite(a, b);
        }
    }
    auto end_dsu = std::chrono::high_resolution_clock::now();

    auto start_naive = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < operations; i++) {
        int op = gen.generateIntegerSequence(1, 0, 1)[0];
        int a = gen.generateIntegerSequence(1, 0, n-1)[0];
        int b = gen.generateIntegerSequence(1, 0, n-1)[0];

        if (op == 0) {
            naive_dsu.get(a);
        } else {
            naive_dsu.unite(a, b);
        }
    }
    auto end_naive = std::chrono::high_resolution_clock::now();

    auto dsu_duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_dsu - start_dsu);
    auto naive_duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_naive - start_naive);

    std::cout << "Performance test for n = " << n << " and " << operations << " operations:" << std::endl;
    std::cout << "DSU time: " << dsu_duration.count() << " ms" << std::endl;
    std::cout << "Naive DSU time: " << naive_duration.count() << " ms" << std::endl;
}


void test_dsu_rollback() {
    DSU dsu(5);
    dsu.unite(0, 1);
    dsu.unite(2, 3);
    int t = dsu.time();
    dsu.unite(0, 2);
    assert(dsu.get(0) == dsu.get(1) && dsu.get(0) == dsu.get(2) && dsu.get(0) == dsu.get(3));
    dsu.rollback(t);
    assert(dsu.get(0) == dsu.get(1) && dsu.get(2) == dsu.get(3) && dsu.get(0) != dsu.get(2));
    std::cout << "DSU rollback test passed." << std::endl;
}

void test_naive_dsu_rollback() {
    NaiveDSU naive_dsu(5);
    naive_dsu.unite(0, 1);
    naive_dsu.unite(2, 3);
    int t = naive_dsu.time();
    naive_dsu.unite(0, 2);
    assert(naive_dsu.get(0) == naive_dsu.get(1) && naive_dsu.get(0) == naive_dsu.get(2) && naive_dsu.get(0) == naive_dsu.get(3));
    naive_dsu.rollback(t);
    assert(naive_dsu.get(0) == naive_dsu.get(1) && naive_dsu.get(2) == naive_dsu.get(3) && naive_dsu.get(0) != naive_dsu.get(2));
    std::cout << "Naive DSU rollback test passed." << std::endl;
}

void stress_test_with_rollback(int n, int operations) {
    RandomGenerators gen;
    DSU dsu(n);
    NaiveDSU naive_dsu(n);

    for (int i = 0; i < operations; i++) {
        int op = gen.generateIntegerSequence(1, 0, 2)[0];
        if (op == 0) {  // get operation
            int a = gen.generateIntegerSequence(1, 0, n-1)[0];
            int b = gen.generateIntegerSequence(1, 0, n-1)[0];
            assert(dsu.get(a) == dsu.get(b) == (naive_dsu.get(a) == naive_dsu.get(b)));
        } else if (op == 1) {  // unite operation
            int a = gen.generateIntegerSequence(1, 0, n-1)[0];
            int b = gen.generateIntegerSequence(1, 0, n-1)[0];
            dsu.unite(a, b);
            naive_dsu.unite(a, b);
        } else {  // rollback operation
            if (dsu.time() > 0) {
                int t = gen.generateIntegerSequence(1, 0, dsu.time() - 1)[0];
                dsu.rollback(t);
                naive_dsu.rollback(t);
            }
        }
    }
    std::cout << "Stress test with rollback passed for n = " << n << " and " << operations << " operations." << std::endl;
}


int main() {
    test_dsu_basic();
    test_naive_dsu_basic();
    test_dsu_rollback();
    test_naive_dsu_rollback();
    
    stress_test(100, 1000);
    stress_test(1000, 10000);
    stress_test_with_rollback(100, 1000);
    stress_test_with_rollback(1000, 10000);
    performance_test(5000, 10000);
    return 0;
}
