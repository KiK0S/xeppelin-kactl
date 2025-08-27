/** 
	* Author: kikos
	* Time: O(n \log^2 n)
	* Description: DCP offline queries
	* Advanced DSU with biconnected components and cycles detection
*/

int dsu[MAXN];
int sz[MAXN];
int parity[MAXN];
int cycle[MAXN];
vector<pair<int*, int>> updates;


pii get(int v) {
	if (dsu[v] == v) return {dsu[v], parity[v]};
	auto [nxt, p] = get(dsu[v]);
	return {nxt, parity[v] ^ p};
}
void unite(int a, int b) {
	auto [x, px] = get(a);
	auto [y, py] = get(b);
	if (x == y) {
		if (px == py) {
			var("cycle " << x << ' ' << y << ' ' << ' ' << a << ' ' << b << ' ' << px << ' ' << py);
			updates.push_back({cycle + x, cycle[x]});
			cycle[x] = 1;
		}
		return;
	}
	if (sz[x] > sz[y]) swap(x, y), swap(px, py);
	updates.push_back({parity + x, parity[x]});
	updates.push_back({dsu + x, dsu[x]});
	updates.push_back({sz + y, sz[y]});
	updates.push_back({cycle + y, cycle[y]});
	parity[x] = 1 ^ px ^ py; dsu[x] = y;
	sz[y] += sz[x]; cycle[y] |= cycle[x];
}
void solve(int v, int tl, int tr) {
	int want = updates.size();
	for (auto p : t[v])
		unite(p.F, p.S);
	auto fix = [&]() {
		while(updates.size() != want) {
			*(updates.back().F) = updates.back().S;
			updates.pop_back();
		}
	};
	// ... solve for leaf, [tl, tm], [tm + 1, tr]; do fix() before returning
}