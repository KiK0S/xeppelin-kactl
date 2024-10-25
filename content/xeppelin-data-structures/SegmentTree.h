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
void upd(int v, int tl, int tr, int pos, int x) { // dont use with pushes!!
	if (tl == tr) {t[v] = x; return;}
	int tm = (tl + tr) / 2;
	if (pos <= tm) upd(2 * v, tl, tm, pos, x); else upd(2 * v + 1, tm + 1, tr, pos, x);
	t[v] = min(t[2 * v], t[2 * v + 1]);
}

// same code for get, just return value instead of updating
void upd(int v, int tl, int tr, int l, int r, int x) {
	push(v, tl, tr);
	if (l > tr || tl > r) return;
	if (l <= tl && tr <= r) {t[v] = x; push(v, tl, tr); return;}
	int tm = (tl + tr) / 2;
	if (pos <= tm) upd(2 * v, tl, tm, l, r, x); else upd(2 * v + 1, tm + 1, tr, l, r, x);
	t[v] = min(t[2 * v], t[2 * v + 1]);
}