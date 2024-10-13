/**
 * Author: Simon Lindholm
 * Date: 2015-02-23
 * License: CC0
 * Source: http://en.wikipedia.org/wiki/Bellman-Ford_algorithm
 * Description: Calculates shortest paths from $s$ in a graph that might have negative edge weights.
 * Time: O(VE)
 * Status: Tested on kattis:shortestpath3
 */
#pragma once

const ll inf = LLONG_MAX;
vector<pair<int, int>> g[MAXN];
int dist[MAXN];

void bellmanFord(int s) {
	dist[s] = 0; // other dists = INF
	// if possible negative cycles: for (i = 0..n) for(edge) relax(edge.to), cycle if relax is success on (n+1)th step
	queue<int> q; vector<int> in_queue(n);
	for (q.push(s); q.size(); q.pop()) {
		int v = q.front(); in_queue[v] = 0;
		for (auto [to, w] : g[v]) {
			if (dist[to] > dist[v] + w) {
				dist[to] = dist[v] + w; // if last iteration and detected neg. cycle -> put -inf.
				if (!in_queue[to]) q.push(to);}}}}
	// to determine if vertex has negative dist: for (i = 0..n) for(edge) if dist[from] = -inf {dist[to] = -inf;}
