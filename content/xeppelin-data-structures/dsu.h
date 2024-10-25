/**
 * Author: Lukas Polacek, Simon Lindholm
 * Date: 2019-12-26
 * License: CC0
 * Source: folklore
 * Description: Disjoint-set data structure with undo.
 * If undo is not needed, skip st, time() and rollback().
 * Usage: int t = uf.time(); ...; uf.rollback(t);
 * Time: $O(\log(N))$
 * Status: tested as part of DirectedMST.h
 */
#pragma once

// for dcp offline: remember updates and perform rollback
void init() {for (int i = 0; i < n; i++) p[i] = i;}
int get(int x) {if (p[x] == x) return x; return p[x] = get(p[x]);}
void unite(int a, int b) {
	a = get(a); b = get(b);
	if (a == b) return;
	if (sz[a] > sz[b]) swap(a, b);
	p[a] = b; sz[b] += sz[a];
}