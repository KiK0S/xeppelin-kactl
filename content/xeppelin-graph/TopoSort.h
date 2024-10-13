/**
 * Author: Unknown
 * Date: 2002-09-13
 * Source: predates tinyKACTL
 * Description: disassemble graph. see 2-sat for dfs-based topsort
 * Time: $O(|V|+|E|)$
 * Status: stress-tested
 */
#pragma once

for (auto& li : gr) for (int x : li) indeg[x]++;
queue<int> q; // use priority_queue for lexic. largest ans.
rep(i,0,sz(gr)) if (indeg[i] == 0) q.push(i);
while (!q.empty()) {
	int i = q.front(); // top() for priority queue
	ret.push_back(i);
	q.pop();
	for (int x : gr[i])
		if (--indeg[x] == 0) q.push(x);
}
