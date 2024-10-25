#include <iostream>
#include "include/random_generators.hpp"

void testSomeAlgorithm() {
    RandomGenerators gen;
    
    // Generate a random integer sequence
    std::vector<int> seq = gen.generateIntegerSequence(10, 1, 100);
    
    // Generate a random graph
    std::vector<std::vector<int>> graph = gen.generateGraph(5, 7);
    
    // Generate a random rooted tree
    std::vector<int> tree = gen.generateRootedTree(6);
    
    // Generate a random permutation
    std::vector<int> perm = gen.generatePermutation(8);
    
    std::cout << "generators are ok\n":
}

int main() {
    testSomeAlgorithm();
    return 0;
}
