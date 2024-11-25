/**
 * Author: Lucian Bicsi
 * Date: 2017-10-31
 * License: CC0
 * Source: folklore
 * Description: Zero-indexed max-tree. Bounds are inclusive to the left and exclusive to the right.
 * Can be changed by modifying T, f and unit.
 * Time: O(\log N)
 * Status: stress-tested
 */
#pragma once

void upd(int v, int x) {
	v += (1 << MAXLOG); t[v] = x;
	while (v != 1) {v >>= 1; t[v] = min(t[2 * v], t[2 * v + 1]);}}

int get(int l, int r) {
	l += (1 << MAXLOG); r += (1 << MAXLOG); int res = inf;
	while (l != r) {
		if (l & 1) res = min(res, t[l++]);
		if (!(r & 1)) res = min(res, t[r--]);
		l >>= 1, r >>= 1;}
	res = min(res, t[l]);}

// if persistent: store left and right child and return updated node from upd to attach in place of previous version
// dont use single position update with pushes!!
void upd(int v, int tl, int tr, int pos, int x) { 
	if (tl == tr) {t[v] = x; return;}
	int tm = (tl + tr) / 2;
	if (pos <= tm) upd(2 * v, tl, tm, pos, x); else upd(2 * v + 1, tm + 1, tr, pos, x);
	t[v] = min(t[2 * v], t[2 * v + 1]);
}

// gets position with sum <= cnt
pair<int, int> get(int v, int tl, int tr, int l, int r, int cnt, int tp) {
	push(v, tl, tr);
	if (r < tl || l > tr) {
		return {-1, 0};
	}
	if (l <= tl && r >= tr && cnt > t[v]) {
		return {-1, t[v]};
	}
	if (tl == tr) {
		return {tl, 0};
	}
	// lazy: if (!v->l) create_lr(v); 
	int tm = (tl + tr) / 2;
	auto p1 = get(v * 2, tl, tm, l, r, cnt, tp);
	if (p1.first != -1) return p1;
	auto p3 = get(v * 2 + 1, tm + 1, tr, l, r, cnt - p1.second, tp);
	p3.second += p1.second;
	return p3;
}
