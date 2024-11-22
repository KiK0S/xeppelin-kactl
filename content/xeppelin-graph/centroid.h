/**
 * Author: kik0s
 * Description: Centroid Decomposition
 * Time: O(N \log N)
 */

int dfs(int v, int p, int sz, int &c) {
	int cnt = 1;
	for (auto to : g[v]) {
		if (used[to] || to == p) continue;
		cnt += dfs(to, v, sz, c);
	}
	if (c == -1 && (cnt * 2 >= sz || p == -1)) c = v;
	return cnt;
}

int find_centroid(int v, int sz, int lg, int p = -1) {
	int c = -1;
	dfs(v, -1, sz, c); // can set new sz
	used[c] = 1;
    // get log n parents in decomposition (if needed)
   	cd[c][lg] = c; for (int i = 0; i < lg; i++) cd[c][i] = cd[p][i];
	
    // solve for all pathes that go through c
    // ie do all vertical paths v -> c & c <- u
    // careful that v and u are from different subtrees of c
    // for (auto to : g[c]) if (!used[to]) {
    //     solve_subtree(to, c);
    //     match_with_previous(to, prev_combined);
    //     merge_results(to, prev_combined);
    // }
    
	for (auto to : g[c]) {
		if (used[to]) continue;
		find_centroid(to, sz / 2, lg + 1, c);
	}
	return c;
}