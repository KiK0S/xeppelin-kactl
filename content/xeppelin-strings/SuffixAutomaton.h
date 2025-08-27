/**
 * Author: grphil
 * Description: Builds suffix automaton for a string. For a suffix tree give a reversed string and take tree of suflinks. if debugging, use aabab
 * Usage: int v = 0; for (auto c : s) { v = add(v, c - 'a'); }
 * Time: O(n)
 */


struct node {
	int to[27];
	int p = -1, len = 0, link = -1, ans = 0, last_used = -1;
	node() {
		memset(to, -1, sizeof(to));
	}
};
int add(int a, int ch) {
	int b = ptr++;
	g[b].len = g[a].len + 1;
	g[b].p = a; g[b].link = 0;
	while (a != -1) {
		if (g[a].to[ch] == -1) {
			g[a].to[ch] = b; g[b].ans += g[a].ans;
			a = g[a].link;
			continue;
		}
		int c = g[a].to[ch];
		if (g[c].p == a) {
			g[b].link = c;
			break;
		}
		int d = ptr++;
		for (int i = 0; i < 27; i++) g[d].to[i] = g[c].to[i];
		g[d].ans = g[c].ans; g[d].link = g[c].link;
    g[b].link = d; g[c].link = d; g[d].p = a;
		g[d].len = g[a].len + 1;
		while (a != -1 && g[a].to[ch] == c) {
			g[a].to[ch] = d;
			g[d].ans += g[a].ans; g[c].ans -= g[a].ans;
			a = g[a].link;
		}
		break;
	}
	return g[g[b].p].to[ch];
}

void subautomaton(int v) {
	if (v < 0 || g[v].last_used == timer) {
		return;
	}
	g[v].last_used = timer;
	g[v].ans++; // here we count strings who had this node
	subautomaton(g[v].link);
	subautomaton(g[v].p);
}