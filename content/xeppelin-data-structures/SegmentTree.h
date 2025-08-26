/**
 * Author: Lucian Bicsi
 * Date: 2017-10-31
 * License: CC0
 * Source: folklore
 * Status: stress-tested
 */
#pragma once

v += (1 << MAXLOG); t[v] = x;
while (v != 1) {v >>= 1; t[v] = min(t[2 * v], t[2 * v + 1]);}

l += (1 << MAXLOG); r += (1 << MAXLOG); int res = inf;
while (l != r) {
	if (l & 1) res = min(res, t[l++]);
	if (!(r & 1)) res = min(res, t[r--]);
	l >>= 1, r >>= 1;}
res = min(res, t[r]);
