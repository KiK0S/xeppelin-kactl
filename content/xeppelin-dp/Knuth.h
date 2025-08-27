/**
 * Author: kik0s
 * Description: when we know $opt_{i,j-1} \leq opt_{i,j} \leq opt_{i+1,j}$, $O(n^2)$
 */

void knuth() { // 
	// .. calc for len 1
	for (int len = 2; len <= n; ++len) {
		for (int i = 0; i + len - 1 <= n; ++i) {
			int j = i + len - 1;
			for (int k = opt[i][j - 1]; k <= opt[i + 1][j]; ++k) {
				if (cost(i, j, k) < cost(i, j, opt[i][j])) {
					opt[i][j] = k;
				}
			}
		}
	}
}