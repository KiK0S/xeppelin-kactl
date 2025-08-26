/**
 * Author: Lukas Polacek
 * Date: 2009-10-28
 * License: CC0
 * Source:
 * Status: works
 */
#pragma once

int timer = 1;
bool find(int j, vector<vi>& g, vi& mt, vi& used) {
	if (mt[j] == -1) return 1;
	used[j] = timer; int di = mt[j];
	for (int e : g[di])
		if (used[e] != timer && find(e, g, mt, used)) {
			mt[e] = di;
			return 1;
		}
	return 0;
}
int dfsMatching(vector<vi>& g, vi& mt) {
	vi vis;
	// do greedy init to speedup
	rep(i,0,sz(g)) {
		timer++;
		for (int j : g[i])
			if (find(j, g, mt, vis)) {
				mt[j] = i;
				break;
			}
	}
	return sz(mt) - (int)count(all(mt), -1);
}
