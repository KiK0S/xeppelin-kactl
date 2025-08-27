/**
 * Author: kik0s
 * Description: having (n, k) problem, try binsearching some penalty for "each k" so that optimal "k" is k 
 */

ll aliens() {
	ll L = -1e13, R = 1e13;
	while (L + 1 < R) {
		ll mid = (L + R) >> 1;
		pair<ll, int> X = check(mid); // returns (ans, k)
		if (X.second > k) {
			R = mid;
		}
		else {
			L = mid;
		}
	}
	pair<ll, int> res = check(R);
	// note res.second is not exactly R, we hope that answer for R is the same
	return res.first - k * R; 
}
