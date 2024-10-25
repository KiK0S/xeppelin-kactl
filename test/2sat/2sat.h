#pragma once
#include <vector>
#include <algorithm>

const int MAXN = 200005; // Adjust this value as needed

struct TwoSat {
    std::vector<std::vector<int>> g, gr;
    std::vector<bool> used, ans;
    std::vector<int> order, comp;
    int n;

    TwoSat(int _n) : n(_n), used(2*_n), ans(_n), order(2*_n), comp(2*_n), g(2*_n), gr(2*_n) {}

    void add_edge(int u, int v) {
        g[u].push_back(v);
        gr[v].push_back(u);
    }

    void add_clause(int u, int v) {
        add_edge(u^1, v);
        add_edge(v^1, u);
    }

    void dfs1(int v) {
        used[v] = true;
        for (int u : g[v]) {
            if (!used[u]) dfs1(u);
        }
        order.push_back(v);
    }

    void dfs2(int v, int cl) {
        comp[v] = cl;
        for (int u : gr[v]) {
            if (comp[u] == -1) dfs2(u, cl);
        }
    }

    bool solve() {
        for (int i = 0; i < 2*n; ++i) {
            if (!used[i]) dfs1(i);
        }
        std::reverse(order.begin(), order.end());
        std::fill(comp.begin(), comp.end(), -1);
        int cl = 0;
        for (int v : order) {
            if (comp[v] == -1) dfs2(v, cl++);
        }
        for (int i = 0; i < n; ++i) {
            if (comp[2*i] == comp[2*i+1]) return false;
            ans[i] = comp[2*i] > comp[2*i+1];
        }
        return true;
    }

    int negation(int v) { return v ^ 1; }
};
