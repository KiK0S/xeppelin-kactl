#ifndef NAIVE_DSU_H
#define NAIVE_DSU_H

#include <vector>
#include <utility>

class NaiveDSU {
private:
    std::vector<int> color;
    std::vector<std::vector<std::pair<int, int>>> history;
    int n;

public:
    NaiveDSU(int size) : n(size), color(size) {
        for (int i = 0; i < n; i++) color[i] = i;
    }

    int get(int x) {
        return color[x];
    }

    void unite(int a, int b) {
        int old_color = color[a];
        int new_color = color[b];
        std::vector<std::pair<int, int>> changes;
        for (int i = 0; i < n; i++) {
            if (color[i] == old_color) {
                changes.emplace_back(i, color[i]);
                color[i] = new_color;
            }
        }
        history.push_back(changes);
    }

    int time() {
        return history.size();
    }

    void rollback(int t) {
        while (history.size() > t) {
            const auto& changes = history.back();
            for (const auto& [index, old_color] : changes) {
                color[index] = old_color;
            }
            history.pop_back();
        }
    }
};

#endif // NAIVE_DSU_H