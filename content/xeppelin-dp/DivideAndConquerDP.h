/**
 * Author: kik0s
 * Description: Given $opt[i][j] \le opt[i][j + 1]$, solve in nmlog
 */
#pragma once

void solve(int layer, int l, int r, int L = 0, int R = n) {
    if (l > r) return;
	int m = (l + r) >> 1;
	opt[layer][m] = L;
	for (int k = L; k <= R; ++k) {
		if (cost(layer, m, k) < cost(layer, m, opt[layer][m])) {
			opt[layer][m] = k;
		}
	}
	solve(layer, l, m - 1, L, opt[layer][m]);
	solve(layer, m + 1, r, opt[layer][m], R);
}
