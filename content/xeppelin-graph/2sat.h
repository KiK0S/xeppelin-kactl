/**
 * Author: Emil Lenngren, Simon Lindholm
 * Date: 2011-11-29
 * License: CC0
 * Source: folklore
 * Description: Calculates a valid assignment to boolean variables a, b, c,... to a 2-SAT problem,
 * Status: stress-tested
 */
#pragma once

vector<int> g[MAXN]; vector<int> gr[MAXN]; vector<int> topsort;
int used[MAXN]; int color[MAXN];

void add_or(int a, int b) {
	g[a^1].push_back(b); g[b^1].push_back(a);
	gr[a].push_back(b^1); gr[b].push_back(a^1);
}

void dfs(int v) {
	if (used[v]) return; used[v] = 1;
	for (auto to : g[v]) dfs(to);
	topsort.push_back(v);
}

void paint(int v, int c /* increment c globally each dfs iteration*/) {
	if (color[v]) return; color[v] = c;
	for (auto to : gr[v]) paint(to, c);
}

void 2sat() {
	forn(i, 2*n) if (!used[i]) dfs(i);
	reverse(all(topsort));
	for (int i : topsort) if (!used[i]) {
		// can skip paint if we know answer exists: earliest in topsort is assigned
		paint(i, C); C++;
	}
	for (int i : vars) {
		if (color[i] == color[i ^ 1]) { /* no solution */ }
		else ans[i] = (color[i] > color[i ^ 1] ? 1 : 0);
	}
}

