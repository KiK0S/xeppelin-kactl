/**
 * Author: isaf27
 * Description: Push lines to a segment tree and query the maximum value at a point.
 */

struct Line {
	ld k = 0, b = -inf; // (check if you need -inf^2)
	ld operator()(ld x) { return k * x + b; }
} a[maxn * 4];
void insert(int tl, int tr, Line s, int v=0) {
	if(tl + 1 == tr) {
		if(s(tl) > a[v](tl)) a[v] = s;
		return;
	}
	int tm = (tl + tr) / 2;
	if(a[v].k > s.k) swap(a[v], s);
	if(a[v](tm) < s(tm)) {
		swap(a[v], s);
		insert(tl, tm, s, 2 * v + 1);
	}
	else insert(tm+1, tr, s, 2 * v + 2);
}
ld query(int v, int tl, int tr, int x) {
	if(tl == tr) return a[v](x);
	int tm = (tl + tr) / 2;
	if(x <= tm) return max(a[v](x), query(2*v, tl, tm, x));
	else return max(a[v](x), query(2*v+1, tm+1, tr, x));
}