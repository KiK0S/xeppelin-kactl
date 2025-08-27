/** 
	* Author: kik0s
	* Description: Disjoint sparse table for static queries where operation can not be split in two overlapping segments
*/
#pragma once

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