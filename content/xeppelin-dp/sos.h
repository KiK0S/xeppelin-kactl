/**
 * Author: kik0s
 * Description: sum over subsets, $O(2^n \cdot n)$
 */

int a[1 << MAXLOG];
ll sos() { // takes 1 << n elements
    for (int i = 0; i < n; i++)
        for (int mask = 0; mask < (1 << n); mask++)
            if (mask & (1 << i))
                a[mask] += a[mask ^ (1 << i)];
}

// having an array of sums of subsets, find the original array
ll rev_sos() {
    for (int mask = 0; mask < (1 << n); mask++) {
		for (int i = 0; i < n; i++) {
            dp[mask][i] = (i == 0 ? 0 : dp[mask][i - 1]);
			if (mask & (1 << i))
				dp[mask][i] += (i == 0 ? ans[mask ^ (1 << i)] : dp[mask ^ (1 << i)][i - 1]);
		}
		ans[mask] = given_sum[mask] - dp[mask][n - 1];
		for (int i = 0; i < n; i++) {
			dp[mask][i] += ans[mask];
		}
    }
}
