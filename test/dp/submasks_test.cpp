#include <iostream>
#include <vector>
#include <cassert>
#include <cstdlib>
#include <ctime>
#include "submasks.h"

void test_submasks_basic() {
    int n = 4;
    std::vector<int> count(1 << n, 0);

    for (int mask = 0; mask < (1 << n); mask++) {
        Submasks::iterate(mask, [&](int submask) {
            count[mask]++;
        });
    }

    for (int mask = 0; mask < (1 << n); mask++) {
        int expected = __builtin_popcount(mask);
        assert(count[mask] == (1 << expected));
    }

    std::cout << "Basic submasks test passed." << std::endl;
}

void test_submasks_random() {
    srand(time(0));
    int n = 10;
    std::vector<int> values(1 << n, 0);
    std::vector<int> sums(1 << n, 0);

    for (int i = 0; i < n; i++) {
        values[i] = rand() % 100;
    }

    for (int mask = 0; mask < (1 << n); mask++) {
        Submasks::iterate(mask, [&](int submask) {
            for (int i = 0; i < n; i++) {
                if (submask & (1 << i)) {
                    sums[mask] += values[i];
                }
            }
        });
    }

    for (int mask = 0; mask < (1 << n); mask++) {
        int sum = 0;
        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) {
                sum += values[i] * (1 << (__builtin_popcount(mask) - 1));
            }
        }
        assert(sums[mask] == sum);
    }

    std::cout << "Random submasks test passed." << std::endl;
}

int main() {
    test_submasks_basic();
    test_submasks_random();
    std::cout << "All submasks tests passed!" << std::endl;
    return 0;
}
