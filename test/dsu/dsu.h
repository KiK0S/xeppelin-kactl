#ifndef DSU_H
#define DSU_H

#include <vector>
#include <tuple>

class DSU {
private:
    std::vector<int> p, sz;
    std::vector<std::tuple<int, int, int>> st; // (node, old_p, old_sz)
    int n;

public:
    DSU(int size) : n(size), p(size), sz(size, 1) {
        init();
    }

    void init() {
        for (int i = 0; i < n; i++) p[i] = i;
    }

    int get(int x) {
        if (p[x] == x) return x;
        // return p[x] = get(p[x]); // but a fancy one with rollback
        int old_p = p[x];
        int root = get(p[x]);
        if (old_p != root) {
            st.emplace_back(x, old_p, sz[x]);
            p[x] = root;
        }
        return root;
    }

    void unite(int a, int b) {
        a = get(a); b = get(b);
        if (a == b) return;
        if (sz[a] > sz[b]) std::swap(a, b);
        st.emplace_back(a, p[a], sz[a]);
        st.emplace_back(b, p[b], sz[b]);
        p[a] = b;
        sz[b] += sz[a];
    }

    int time() { return st.size(); }

    void rollback(int t) {
        while (st.size() > t) {
            auto [node, old_p, old_sz] = st.back();
            p[node] = old_p;
            sz[node] = old_sz;
            st.pop_back();
        }
    }
};

#endif // DSU_H
