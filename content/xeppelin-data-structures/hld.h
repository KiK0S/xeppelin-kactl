/**
 * Author: zban
 * Description: Heavy-light decomposition.
 * To remove extra log, precache the answer for each path on the prefix, then you query prefixes in O(1) and one segment in O(log).
 */

const int N = 1 << 17;
// par - parent, heavy - heavy child, h - depth
int par[N], heavy[N], h[N], sz[N];
int root[N], pos[N];
int n;
vector<int> g[N];

void dfs(int v) {
    sz[v] = 1; int mx = 0;
    for (int i = 0; i < g[v].size(); ++i) {
        int to = g[v][i];
        if (to == par[v]) {
            // remove the edge to the parent
            swap(g[v][i], g[v].back());
            g[v].pop_back(); --i; continue;
        }
        par[to] = v; h[to] = h[v] + 1; sz[v] += sz[to];
        dfs(to);
        if (sz[to] > mx) {
            heavy[v] = to, mx = sz[to];
            swap(g[v][0], g[v][i]); // with this swap we can query subtrees too.
        }
    }
}

// op(l, r) - update the answer on the path from l to r
int path(int u, int v) {
    int sum = 0;
    for (; root[u] != root[v]; v = par[root[v]]) {
        if (h[root[u]] > h[root[v]]) swap(u, v);
        sum += segtree.get(pos[root[v]], pos[v]);
    }
    if (h[u] > h[v]) swap(u, v);
    sum += segtree.get(pos[u], pos[v]); return sum;
}

int subtree(int v) { return segtree.get(pos[v], pos[v] + sz[v] - 1); }

void init() {
    memset(heavy, -1, sizeof(heavy[0]) * n);
    par[0] = -1;
    h[0] = 0;
    dfs(0);
    for (int i = 0, cpos = 0; i < n; i++) {
        if (par[i] == -1 || heavy[par[i]] != i) {
            for (int j = i; j != -1; j = heavy[j]) {
                root[j] = i;
                pos[j] = cpos++;
                segtree.upd(pos[j], val[j]);
            }
        }
    }
}
