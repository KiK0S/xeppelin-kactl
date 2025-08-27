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

void dfs(int v, int p = -1) {
	sz[v] = 1;
	int id = -1;
	for (int i = 0; i < g[v].size(); i++) {
		int to = g[v][i];
		if (to == par[v]) {
			// remove the edge to the parent
			swap(g[v][i], g[v].back());
			g[v].pop_back(); --i; continue;
		}
		dfs(to, v);
		if (sz[to] > sz[g[v][id]]) {
			id = i;
		}
		sz[v] += sz[to];
	}
	if (id != -1) swap(g[v][id], g[v][0]);
}

void build(int v, int p) {
	if (up[v] == -1)
		up[v] = up[p];
	pos[timer] = v;
	tin[v] = timer++;
	bool f = 0;
	for (auto to : g[v]) {
		if (f)
			up[to] = to;
		build(to, v);
		f = 1;
	}
	tout[v] = tin[v] + sz[v] - 1;
}

int path(int u, int v) {
	int sum = 0;
	for (; root[u] != root[v]; v = par[root[v]]) {
		if (h[root[u]] > h[root[v]]) swap(u, v);
		sum += segtree.get(pos[root[v]], pos[v]);
	}
	if (h[u] > h[v]) swap(u, v);
	sum += segtree.get(pos[u], pos[v]); return sum;
	// this works for vertices. for edges vertical paths should probably work on (l, r]
}

int subtree(int v) { return segtree.get(pos[v], pos[v] + sz[v] - 1); }
