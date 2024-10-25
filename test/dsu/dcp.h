#ifndef DCP_H
#define DCP_H

#include <vector>
#include <functional>
#include <map>
#include "dsu.h"

struct Query {
    int type; // 0: add, 1: remove, 2: get
    int u, v;
    int index; // for get queries
};

class DCP {
private:
    std::vector<std::vector<Query>> t;
    int n;
    DSU dsu;
    std::vector<int> ans;

public:
    DCP(int size, int N) : n(size), dsu(N) {
        t.resize(4 * n);
        ans.resize(n, -1);
    }

    void update(int l, int r, const Query& q) {
        std::function<void(int, int, int, int, int)> add = [&](int v, int tl, int tr, int l, int r) {
            if (r < tl || tr < l) return;
            if (l <= tl && tr <= r) {
                t[v].push_back(q);
                return;
            }
            int tm = tl + (tr - tl) / 2;
            add(2 * v, tl, tm, l, r);
            add(2 * v + 1, tm + 1, tr, l, r);
        };
        add(1, 0, n - 1, l, r);
    }

    std::vector<int> dcp() {
        std::function<void(int, int, int)> process = [&](int v, int l, int r) {
            int time = dsu.time();
            for (const auto& q : t[v]) {
                if (q.type == 0) {
                    dsu.unite(q.u, q.v);
                } 
            }
            for (const auto& q : t[v]) {
                if (q.type == 2) {
                    ans[q.index] = dsu.get(q.u) == dsu.get(q.v);
                }
            }
            
            if (l == r) {
                dsu.rollback(time);
                return;
            }
            
            int mid = l + (r - l) / 2;
            process(2 * v, l, mid);
            process(2 * v + 1, mid + 1, r);
            
            dsu.rollback(time);
        };
        process(1, 0, n - 1);
        return ans;
    }
};

std::vector<int> solve(const std::vector<Query>& queries, int N) {
    // Count get operations to determine DCP size
    int dcp_size = 0;
    for (const auto& q : queries) {
        if (q.type == 2) dcp_size++;
    }
    DCP solver(dcp_size, N);
    
    // Process add and remove queries
    std::map<std::pair<int, int>, int> edge_to_add_index;
    int ptr = 0;
    for (int i = 0; i < queries.size(); i++) {
        if (queries[i].type == 0) { // add
            edge_to_add_index[{queries[i].u, queries[i].v}] = ptr;
        } else if (queries[i].type == 1) { // remove
            auto it = edge_to_add_index.find({queries[i].u, queries[i].v});
            if (it != edge_to_add_index.end()) {
                int add_index = it->second;
                if (add_index != ptr) solver.update(add_index, ptr - 1, {0, queries[i].u, queries[i].v, -1});
                edge_to_add_index.erase(it);
            }
        } else if (queries[i].type == 2) { // get
            solver.update(ptr, ptr, {2, queries[i].u, queries[i].v, ptr});
            ptr++;

        }
    }
    
    // Process remaining add queries that weren't removed
    for (const auto& [edge, add_index] : edge_to_add_index) {
        solver.update(add_index, ptr, {0, edge.first, edge.second, -1});
    }

    return solver.dcp();
}
#endif // DCP_H
