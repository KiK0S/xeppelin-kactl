/**
 * Author: kik0s
 * Description: Lazy dp / bfs. suflink ups for caab: $caab \to aab \to ab \to a \to root$.
 * two main formulas go[v][c] = go[suflink(v)][c], suflink[v] = go(suflink(parent[v]), pchar[v]).
 * 
 */
#pragma once


struct V{ int parent; int pchar; int link; int go[26]; /*for fast answer int term_link;*/ };

queue<int> q; q.push(0);
for (q.push(0); !q.empty(); q.pop()) {
	V v = /*cast*/ q.front();
	for (/* char c */) {
		// can also do while(go[p][c] == -1) p = suflink[p]
		// but doesnt build explisit automaton 
		suflink[v] = go[suflink[parent[v]]][pchar[v]];
		tree[suflink[v]].push_back(v);
		if (go[v][c] == -1) go[v][c] = go[suflink[v]][c];
		else q.push(go[v][c]);
	}
}
