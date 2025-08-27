/**
 * Author: isaf27
 * Description: Euler tour tree.
 * Stores edges in a tree, but reroot() accepts a vertex.
 * mn[v] stores minimum in treap's subtree. For a$\to$b, we store val[a] in the vertex. To see all occurences of the vertex value, abuse adj[v].
 */

 void recalc(int v) {
    if (!v) return;
    mn[v] = val[v];
    if (c[v][0]) mn[v] = min(mn[v], mn[c[v][0]]);
    if (c[v][1]) mn[v] = min(mn[v], mn[c[v][1]]);
}
int getRoot(int x) { // get top node in ETT
	while (par[x]) x = par[x];
	return x;
}
void link(int x, int d, int y) { // set d-th child of x to y
	c[x][d] = y; if (y) par[y] = x;
    recalc(x); recalc(y);
}
int dis(int x, int d) { // disconnected d-th child of x
	int y = c[x][d]; c[x][d] = 0;
	if (y) par[y] = 0;
    recalc(y); recalc(x);
    return y;
}
pi split(int x) { // x and everything to right goes in p.s
	// everything else goes in p.f
	pi p = {dis(x,0),x};
	while (par[x]) {
		int y = par[x];
		if (c[y][0] == x) {
			dis(y,0), link(y,0,p.s),  p.s = y;
		} else {
			dis(y,1), link(y,1,p.f); p.f = y;
		}
		x = y;
	}
    return p;
}

int merge(int x, int y) {
    recalc(x); recalc(y);
	if (!x || !y) return max(x,y);
	if (pri[x] > pri[y]) {
		int X = dis(x,1);
		link(x,1,merge(X,y));
        recalc(x); return x;
	} else {
		int Y = dis(y,0);
		link(y,0,merge(x,Y));
        recalc(y); return y;
	}
}

int getFirst(int x) {
	if (!x) return 0;
	while (c[x][0]) x = c[x][0];
	return x;
}
int makeFirst(int x) { // rotate ETT of x such that x is first
    pi p = split(x);
	return merge(p.s,p.f);
}
void remFirst(int x) { // remove first node of ETT rooted at x
	while (c[x][0]) x = c[x][0];
	int y = dis(x,1), p = par[x];
	if (p) dis(p,0), link(p,0,y);
}

map<int,int> adj[MX];
int makeEdge(int a, int b) {
	adj[a][b] = ++cnt; pri[cnt] = rng();
    val[cnt] = mn[cnt] = a;
    return cnt;
}
int reroot(int x) { // make edge beginning with x
	if (!sz(adj[x])) return 0;
	return makeFirst(begin(adj[x])->s);
}
bool con(int a, int b) {
	if (!sz(adj[a]) || !sz(adj[b])) return 0;
	a = begin(adj[a])->s, b = begin(adj[b])->s;
	return getRoot(a) == getRoot(b);
}
void add(int a, int b) { // connect A and B with edge
	int ta = reroot(a), tb = reroot(b);
	int x = makeEdge(a,b), y = makeEdge(b,a); // make two nodes for new edge
	merge(merge(ta,x),merge(tb,y));
}
void rem(int a, int b) {
	int x = adj[a][b], y = adj[b][a];
    val[x] = INF, val[y] = INF;
    makeFirst(x);
	pi p = split(y);
	remFirst(p.f), remFirst(p.s);
	adj[a].erase(b), adj[b].erase(a);
}