/**
 * Author: isaf27
 * Description: Push lines to a segment tree and query the maximum value at a point.
 */

struct Line {
	ld k = 0, b = -inf; // (check if you need -inf^2)
	ld operator()(ld x) { return k * x + b; }
} a[maxn * 4];
void insert(int l, int r, Line s, int v=0) {
	if(l + 1 == r) {
		if(s(l) > a[v](l)) a[v] = s;
		return;
	}
	int m = (l + r) / 2;
	if(a[v].k > s.k) swap(a[v], s);
	if(a[v](m) < s(m)) {
		swap(a[v], s);
		insert(l, m, s, 2 * v + 1);
	}
	else insert(m, r, s, 2 * v + 2);
}
ld query(int l, int r, int x, int v=0) {
	if(l + 1 == r) return a[v](x);
	int m = (l + r) / 2;
	if(x < m) return max(a[v](x), query(l, m, x, 2 * v + 1));
	else return max(a[v](x), query(m, r, x, 2 * v + 2));
}