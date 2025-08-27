/**
	* Author: kik0s
	* Description: Descend a virtual segtree (from two persistent roots) to find the element with prefix sum $\geq k$.
	* If query is on a segment (and in regular segtree) write usual get-checks, iterate both left and right, but if you are inside a segment, do break if not enough values
	*/
#pragma once

int descend(int vl, int vr, int tl, int tr, int k) {
	if (tl == tr) {
		int ss = 0;
		if (vl != -1) ss -= t[vl].sum;
		if (vr != -1) ss += t[vr].sum;
		if (k >= ss) {
			return tl+1;
		}
		return tl;
	}
	int l = -1, r = -1;
	if (vl != -1) l = t[vl].l;
	if (vr != -1) r = t[vr].l;
	int s = 0;
	if (l != -1) s -= t[l].sum;
	if (r != -1) s += t[r].sum;
	int tm = (tl + tr) / 2;
	if (s <= k) {
		return descend(vl == -1 ? -1 : t[vl].r, vr == -1 ? -1 : t[vr].r, tm+1, tr, k-s);
	}
	return descend(vl == -1 ? -1 : t[vl].l, vr == -1 ? -1 : t[vr].l, tl, tm, k);
}