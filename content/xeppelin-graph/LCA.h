/**
 * Author: chilli, pajenegod
 * Date: 2020-02-20
 * License: CC0
 * Source: Folklore
 * Description: Data structure for computing lowest common ancestors in a tree
 * (with 0 as root). C should be an adjacency list of the tree, either directed
 * or undirected.
 * Time: $O(N \log N + Q)$
 * Status: stress-tested
 */
#pragma once

#include "../data-structures/RMQ.h"

void dfs(int v, int p = -1, int h = 0) {
	tin[v] = path.size();
	path.push_back({d[v], v});
	for (int y : g[v]) if (y != par) {
		dfs(y, v, h + 1);
		path.push_back({d[v], v});
	}
	tout[v] = path.size() - 1;
}
int lca(int a, int b){return rmq(min(tin[a], tin[b]), max(tout[a], tout[b])).second;}
int dist(a,b){return depth[a] + depth[b] - 2*depth[lca(a,b)];}
