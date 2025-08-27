/**
 * Author: kik0s
 * Description: Lazy dp / bfs. suflink ups for caab: $caab \to aab \to ab \to a \to root$.
 * two main formulas go[v][c] = go[suflink(v)][c], suflink[v] = go(suflink(parent[v]), pchar[v]).
 * 
 */
#pragma once

void build_automaton() {
	queue<int> q;
	G[0].suflink = 0;
	for (int c = 0; c < 26; ++c) {
		int u = G[0].go[c];
		if (u == -1) G[0].go[c] = 0;
		else {
			G[u].suflink = 0; G[0].tree.push_back(u); // suffix tree edge
			q.push(u);
		}
	}
	while (!q.empty()) {
		int v = q.front(); q.pop();
		for (int c = 0; c < 26; ++c) {
			int u = G[v].go[c];
			if (u == -1)
				G[v].go[c] = G[G[v].suflink].go[c];
			else {
				G[u].suflink = G[G[v].suflink].go[c];
				G[G[u].suflink].tree.push_back(u); // suffix tree edge
				q.push(u);
			}
		}
	}
}
