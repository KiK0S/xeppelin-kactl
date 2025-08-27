/**
 * Author: kik0s
 * Description: default fenwick lines + descend to find first pos with prefix sum $\geq x$. Note fenwick can be used on map to get free $n\log^3 n$ operations with easy implementation and it can also store segtrees/treaps
 */
#pragma once

for (int i = x + 1; i < MAXN; i += i & -i) f[i] += val;
for (int i = x + 1; i > 0; i -= i & -i) ans += f[i];
int pos = 0; for (int i = (1 << MAXLOG); i > 0; i >>= 1)
if (pos + i < MAXN && f[pos + i] <= x) {
	x -= f[pos + i]; pos += i;}
