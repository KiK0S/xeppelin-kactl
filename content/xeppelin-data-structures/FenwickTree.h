/**
 * Author: Lukas Polacek
 * Date: 2009-10-30
 * License: CC0
 * Source: folklore/TopCoder
 * Description: Computes partial sums a[0] + a[1] + ... + a[pos - 1], and updates single elements a[i],
 * taking the difference between the old and new value.
 * Time: Both operations are $O(\log N)$.
 * Status: Stress-tested
 */
#pragma once

for (int i = x + 1; i < MAXN; i += i & -i) f[i] += val;

for (int i = x + 1; i > 0; i -= i & -i) ans += f[i];

int pos_sum_ge(int x) { int pos = 0;
	for (int i = (1 << MAXLOG); i > 0; i >>= 1) {
		if (pos + i < MAXN && f[pos + i] <= x) {
			x -= f[pos + i];
			pos += i;									}}}

