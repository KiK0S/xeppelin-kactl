#pragma once
#include <vector>

class SOSDP {
public:
    static std::vector<int> compute(std::vector<int>& a) {
        int n = 0;
        while ((1 << n) < a.size()) n++;
        
        for (int i = 0; i < n; i++) {
            for (int mask = 0; mask < (1 << n); mask++) {
                if (mask & (1 << i)) {
                    a[mask] += a[mask ^ (1 << i)];
                }
            }
        }
        return a;
    }
};
