/**
 * Author: Johan Sannemo, pajenegod
 * Date: 2015-02-06
 * License: CC0
 * Source: Folklore
 * Description: $O(1)$ query, $O(n \log n)$ memory. If $i + 2^j > n$, it's never achievable
 * Status: stress-tested
 */
#pragma once

lg[1] = 0; for (int i = 2; i < MAXN; i++) lg[i] = lg[i >> 1] + 1;
for (int i = 0; i < n; i++) table[0][i] = a[i];
for (int j = 1; j < MAXLOG; j++) for (int i = 0; i + (1 << j) <= n; i++)
table[j][i] = min(table[j - 1][i], table[j - 1][(i + (1 << (j - 1)))]);

int lvl = lg[r - l + 1];
return min(table[lvl][l], table[lvl][r - (1 << lvl) + 1]);
