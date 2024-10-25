/**
 * Author: Johan Sannemo, pajenegod
 * Date: 2015-02-06
 * License: CC0
 * Source: Folklore
 * Description: Range Minimum Queries on an array. Returns
 * min(V[a], V[a + 1], ... V[b - 1]) in constant time.
 * Usage:
 *  RMQ rmq(values);
 *  rmq.query(inclusive, exclusive);
 * Time: $O(|V| \log |V| + Q)$
 * Status: stress-tested
 */
#pragma once

int table[MAXLOG][MAXN]; // if slow - swap :-)
int lg[MAXN];
void build() {
	lg[1] = 0; for (int i = 2; i < MAXN; i++) lg[i] = lg[i >> 1] + 1;
	for (int i = 0; i < n; i++) table[0][i] = a[i];
	for (int j = 1; j < MAXLOG; j++) for (int i = 0; i + (1 << j) <= n; i++)
	table[j][i] = min(table[j - 1][i], table[j - 1][(i + (1 << (j - 1)))]);
}
int query(int l, int r) {
	int lvl = lg[r - l + 1];
	return min(table[lvl][l], table[lvl][r - (1 << lvl) + 1]);
}

lg[0] = MAXLOG - 1; for (int i = 1; i < MAXN; i++) lg[i] = lg[i >> 1] - 1;
void build_disjoint(int level=0, int tl=0, int tr=(1 << MAXLOG) - 1) {
	int tm = (tl + tr) / 2;int cur = inf;
	for (int i = tm; i >= tl; i--) {
		table[level][i] = min(cur, a[i]);
		cur = table[level][i];
	}
	cur = inf;
	for (int i = tm + 1; i <= tr; i++) {
		table[level][i] = min(cur, a[i]);
		cur = table[level][i];
	}
	if (tl == tr) return;
	build_disjoint(level + 1, tl, tm);
	build_disjoint(level + 1, tm + 1, tr);
}
int query_disjoint(int l, int r) {
	int lvl = lg[r ^ l];
	return min(table[lvl][l], table[lvl][r]);
}
