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
void make_or(int v1, int v2) {
	g[v1 ^ 1].push_back(v2); gr[v2].push_back(v1 ^ 1);
	g[v2 ^ 1].push_back(v1); gr[v1].push_back(v2 ^ 1);
}

void dfs(int v) {
	if (used[v]) return; used[v] = 1;
	for (auto to : g[v]) dfs(to);
	topsort.push_back(v);
}

void assign_color(int v, int c /* increment c globally each dfs iteration*/) {
	if (color[v]) return; color[v] = c;
	for (auto to : gr[v]) assign_color(to, c);
}

dfs(/* all */); reverse(topsort.begin(), topsort.end());
assign_color(/*all*/);

for (int i : vars) {
	if (color[i] == color[i ^ 1]) {}// no solution
	else ans[i] = (color[i] > color[i ^ 1] ? 1 : 0);
}
