/**
 * Author: Simon Lindholm
 * Date: 2015-02-23
 * License: CC0
 * Source: http://en.wikipedia.org/wiki/Bellman-Ford_algorithm
 * Description: Calculates shortest paths and reconstructs a negative cycle if it exists.
 * Status: Tested on kattis:shortestpath3
 */
#pragma once
for (int i = 0; i < n; ++i) {
	x = -1;
	for (Edge e : edges) {
		if (d[e.a] + e.cost < d[e.b]) {
			d[e.b] = max(-INF, d[e.a] + e.cost);
			p[e.b] = e.a;
			x = e.b;			}}}

if (x == -1)
	cout << "No negative cycle found.";
else {
	for (int i = 0; i < n; ++i)
		x = p[x];
	for (int v = x;; v = p[v]) {
		cycle.push_back(v);
		if (v == x && cycle.size() > 1)
			break;
	}
	reverse(cycle.begin(), cycle.end());
}