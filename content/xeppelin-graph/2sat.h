/**
 * Author: Emil Lenngren, Simon Lindholm
 * Date: 2011-11-29
 * License: CC0
 * Source: folklore
 * Description: Calculates a valid assignment to boolean variables a, b, c,... to a 2-SAT problem,
 * Status: stress-tested
 */
#pragma once

int negation(int v) {return v ^ 1;}
vector<int> g[MAXN]; vector<int> gr[MAXN]; vector<int> topsort;
void dfs(int v) {
	if (used[v]) return; used[v] = 1;
	for (auto to : g[v]) dfs(v);
	topsort.push_back(v);
}

void assign_color(int v, int c /* increment c globally each dfs iteration*/) {
	if (color[v]) return; color[v] = c;
	for (auto to : gr[v]) assign_color(v, c);
}

dfs(/* all */); reverse(topsort.begin(), topsort.end());
assign_color(/*all*/);

for (int i : vars) {
	if (color[i] == color[negation[i]]) {}// no solution
	else ans[i] = (color[i] < color[negation[i]] ? 1 : 0);
}
