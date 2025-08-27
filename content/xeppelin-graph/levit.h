/**
 * Author: emaxx
 * Description: Levit's algorithm for shortest paths in a graph with negative weights. works fast, near $m\log n$.
 */
#pragma once

vector<ll> levit(int n, vector<vector<pair<int, ll>>> &g, int s) {
    vector<ll> d(n, INF), state(n, 2);
    queue<int> q1, q2;
    d[s] = 0; state[s] = 1; q1.push(s);
    while (!q1.empty() || !q2.empty()) {
        int u;
        if (!q2.empty()) { u = q2.front(); q2.pop(); }
        else { u = q1.front(); q1.pop(); }
        for (auto [v, w] : g[u]) {
            if (state[v] == 2) {
                d[v] = d[u] + w;
                state[v] = 1;
                q1.push(v);
            } else if (state[v] == 1 && d[v] > d[u] + w) {
                d[v] = d[u] + w;
            } else if (state[v] == 0 && d[v] > d[u] + w) {
                d[v] = d[u] + w;
                state[v] = 1;
                q2.push(v);
            }
        }
        state[u] = 0;
    }
    return d;
}