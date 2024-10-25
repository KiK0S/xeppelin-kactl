#include "2sat.h"
#include <cassert>
#include <iostream>

void test_basic() {
    TwoSat ts(2);
    ts.add_clause(0, 2);
    assert(ts.solve());
    assert(ts.ans[0] || ts.ans[1]);
}

void test_unsatisfiable() {
    TwoSat ts(1);
    ts.add_clause(0, 0);
    ts.add_clause(1, 1);
    assert(!ts.solve());
}

void test_complex() {
    TwoSat ts(4);
    ts.add_clause(0, 2);
    ts.add_clause(1, 4);
    ts.add_clause(3, 6);
    ts.add_clause(5, 7);
    assert(ts.solve());
    assert(ts.ans[0] || ts.ans[1]);
    assert(!ts.ans[0] || ts.ans[2]);
    assert(ts.ans[1] || !ts.ans[3]);
    assert(!ts.ans[1] || !ts.ans[2]);
}

int main() {
    test_basic();
    test_unsatisfiable();
    test_complex();
    
    std::cout << "All tests passed!" << std::endl;
    return 0;
}
