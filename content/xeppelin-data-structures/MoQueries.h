/**
 * Author: Simon Lindholm
 * Date: 2019-12-28
 * License: CC0
 * Source: https://github.com/hoke-t/tamu-kactl/blob/master/content/data-structures/MoQueries.h
 * Description: Answer interval or tree path queries by finding an approximate TSP through the queries,
 * and moving from one query to the next by adding/removing points at the ends.
 * If values are on tree edges, change \texttt{step} to add/remove the edge $(a, c)$ and remove the initial \texttt{add} call (but keep \texttt{in}).
 * Time: O(N \sqrt Q)
 * Status: stress-tested
 */
#pragma once

void add(int ind, int end) { ... } // add a[ind] (end = 0 or 1)
void del(int ind, int end) { ... } // remove a[ind]
int calc() { ... } // compute current answer

int L = 0, R = 0, blk = 350; // ~N/sqrt(Q)
vi s(sz(Q)), res = s;
#define K(x) pii(x.first/blk, x.second ^ -(x.first/blk & 1))
iota(all(s), 0);
sort(all(s), [&](int s, int t){ return K(Q[s]) < K(Q[t]); });
// also can group by blocks, move right via add, move left sqrt steps and then rollback()
for (int qi : s) {
	pii q = Q[qi];
	while (L > q.first) add(--L, 0); while (R < q.second) add(R++, 1);
	while (L < q.first) del(L++, 0); while (R > q.second) del(--R, 1);
	res[qi] = calc();}

// for trees; if problem on vertices: also add lca
if (tin[a] > tin[b]) swap(a, b);
if (tin[a] <= tin[b] && tin[b] < tin[a] + sz[a]) l = tin[a], r = tin[b]; 
else l = tout[a], r = tin[b];
