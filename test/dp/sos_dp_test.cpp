#include <iostream>
#include <vector>
#include <cassert>
#include <cstdlib>
#include <ctime>
#include "sos_dp.h"

void test_sos_basic() {
    std::vector<int> a = {1, 2, 3, 4};
    auto result = SOSDP::compute(a);

    assert(result[0] == 1);
    assert(result[1] == 3);
    assert(result[2] == 4);
    assert(result[3] == 10);

    std::cout << "Basic SOS DP test passed." << std::endl;
}

void test_sos_random() {
    srand(time(0));
    int n = 10;
    std::vector<int> a(1 << n);
    std::vector<int> b(1 << n);

    for (int i = 0; i < (1 << n); i++) {
        a[i] = rand() % 100;
        b[i] = a[i];
    }

    auto result = SOSDP::compute(a);

    for (int mask = 0; mask < (1 << n); mask++) {
        int sum = 0;
        for (int submask = mask; submask > 0; submask = (submask - 1) & mask) {
            sum += b[submask];
        }
        sum += b[0];
        assert(result[mask] == sum);
    }

    std::cout << "Random SOS DP test passed." << std::endl;
}

int main() {
    test_sos_basic();
    test_sos_random();
    std::cout << "All SOS DP tests passed!" << std::endl;
    return 0;
}
