#include "2sat.h"
#include <iostream>

int main() {
    TwoSat ts(4);
    
    // (x1 || x2) && (!x1 || x3) && (x2 || !x4) && (!x2 || !x3)
    ts.add_clause(0, 2);
    ts.add_clause(1, 4);
    ts.add_clause(3, 6);
    ts.add_clause(5, 7);

    bool satisfiable = ts.solve();
    
    if (satisfiable) {
        std::cout << "Satisfiable!" << std::endl;
        for (int i = 0; i < 4; ++i) {
            std::cout << "x" << i+1 << " = " << ts.ans[i] << std::endl;
        }
    } else {
        std::cout << "Not satisfiable!" << std::endl;
    }

    return 0;
}
