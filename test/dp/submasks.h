#pragma once
#include <vector>
#include <functional>

class Submasks {
public:
    static void iterate(int mask, const std::function<void(int)>& f) {
        for (int submask = mask; submask > 0; submask = (submask - 1) & mask) {
            f(submask);
        }
        f(0);  // Include the empty submask
    }
};
