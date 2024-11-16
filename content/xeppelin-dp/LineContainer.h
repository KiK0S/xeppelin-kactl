/**
 * Author: Simon Lindholm
 * Date: 2017-04-20
 * License: CC0
 * Source: own work
 * Description: Container where you can add lines of the form kx+m, and query maximum values at points x.
 *  Useful for dynamic programming (``convex hull trick'').
 * Time: O(\log N)
 * Status: stress-tested
 */
#pragma once

struct Line {
	mutable ll k, m, p;
	bool operator<(const Line& o) const { return k < o.k; }
	bool operator<(ll x) const { return p < x; }
};

struct LineContainer : multiset<Line, less<>> {
	// (for doubles, use inf = 1/.0, div(a,b) = a/b)
	static const ll inf = LLONG_MAX;
	ll div(ll a, ll b) { // floored division
		return a / b - ((a ^ b) < 0 && a % b); }
	bool isect(iterator x, iterator y) {
		if (y == end()) return x->p = inf, 0;
		if (x->k == y->k) x->p = x->m > y->m ? inf : -inf;
		else x->p = div(y->m - x->m, x->k - y->k);
		return x->p >= y->p;
	}
	void add(ll k, ll m) {
		auto z = insert({k, m, 0}), y = z++, x = y;
		while (isect(y, z)) z = erase(z);
		if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
		while ((y = x) != begin() && (--x)->p >= y->p)
			isect(x, erase(y));
	}
	ll query(ll x) {
		assert(!empty());
		auto l = *lower_bound(x);
		return l.k * x + l.m;
	}
};

struct LiChaoTreeNode {
	LiChaoTreeNode *l, *r;
	Line line;
};

void lichao_add_line(LiChaoTreeNode *v, int tl, int tr, Line l) {
	int tm = (tl + tr) / 2; 
	int cur = l.k * tm + l.m;
	int vcur = v->line.k * tm + v->line.m;
	if (cur > vcur) {
		swap(l, v->line);
	}
	if (tl == tr) return;
	// create childs of v, if havent yet
	if (l.k < v->line.k) lichao_add_line(v->l, tl, tm, l);
	else lichao_add_line(v->r, tm + 1, tr, l);
}

int lichao_get_max(LiChaoTreeNode *v, int tl, int tr, int x) {
	if (tl == tr) return v->line.k * x + v->line.m;
	int tm = (tl + tr) / 2;
	int cur = v->line.k * x + v->line.m;
	if (x < tm) return max(lichao_get_max(v->l, tl, tm, x), cur);
	else return max(lichao_get_max(v->r, tm + 1, tr, x), cur);
}
