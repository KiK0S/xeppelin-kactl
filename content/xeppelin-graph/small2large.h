/**
 * Author: kikos
 * Description: Small to Large optimization.
 * Merge all the sets to the largest one while processing in dfs.
 * if you work not with subtree sizes, but subtree depth, works in linear time.
 */

 void dfs(int v, int p = -1) {
	int mx = 0, argmax = -1;
	for (auto to : g[v]) {
		if (to == p) continue;
		dfs(to, v);
		if (sets[to].size() > mx) {
			mx = sets[to].size();
			argmax = to;
		}
	}
	if (argmax != -1) sets[v].swap(sets[argmax]);
	sets[v].insert(val[v]);
	for (auto to : g[v]) {
		if (to == p || to == argmax) continue;
        // also can add something to answer here: match dp from one subtree with another
        sets[v].insert(sets[to].begin(), sets[to].end());
	}
}