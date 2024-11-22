/**
 * Author: kik0s
 * Description: s sqrt(s) / 64
 */
#pragma once

int costs[MAXN];
bitset<MAXW> knapsack() {
	sort(costs, costs + n);
	vector<int> items;
	for (int i = 0; i < n; i++) {
		int cnt = 1;
		while (i + 1 < n && costs[i + 1] == costs[i]) i++, cnt++;
		for (int j = 1; j <= cnt; j *= 2) {
			items.push_back(j * costs[i]);
			cnt -= j;
		}
		if (cnt > 0) items.push_back(cnt * costs[i]);
	}
	bitset<MAXW> dp;
	dp[0] = 1;
	for (int item : items) dp |= dp << item;
	return dp;
}
