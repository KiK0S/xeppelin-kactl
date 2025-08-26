/*
    * Author: kikos
    * Description: Euler tour tree. Treap with support for parents
    * The actual Euler tour part is not implemented
    * Order of elements stored in the tree is pre + post order combined
*/


// Treap: support for 
struct node {
    int sz, x, y, l, r, p, pc;
    node(int x = 0): x(x) {
        y = rng(); sz = 1;
        push = 0;
        l = -1; r = -1; p = -1;
    }
};

node T[MAXN];

int getsz(int v) { return v == -1 ? 0 : T[v].sz; }

void push(int v) {
    if (v == -1) return; /* todo:actual push needed for problem */ T[v].push = 0;
}

void recalc(int v) {
    if (v == -1) return;
    T[v].sz = getsz(T[v].l) + getsz(T[v].r) + 1;
    if (T[v].l != -1) T[T[v].l].p = v;
    if (T[v].r != -1) T[T[v].r].p = v;
    T[v].p = -1;
}

int pos(int v) {
    int sz = getsz(T[v].l);
    while (T[v].p != -1) {
        int old_v = v; v = T[v].p;
        if (T[v].l != -1) sz += getsz(T[v].l) + 1;
    }
    return sz;
}

int get_comp_root(int v) {
    while (T[v].p != -1) v = T[v].p;
    return v;
}

pair<int, int> split(int v, int k) {
    if (v == -1) return {-1, -1};
    push(v);
    if (getsz(T[v].l) >= k) {
        auto pa = split(T[v].l, k);
        if (pa.F != -1) T[pa.F].p = -1;
        if (pa.S != -1) T[pa.S].p = -1;
        T[v].l = pa.S;
        recalc(v);
        return {pa.F, v};
    } else {
        auto pa = split(T[v].r, k - getsz(T[v].l) - 1);
        if (pa.F != -1) T[pa.F].p = -1;
        if (pa.S != -1) T[pa.S].p = -1;
        T[v].r = pa.F;
        recalc(v);
        return {v, pa.S};
    }
}

int merge(int l, int r) {
    push(l); push(r);
    recalc(l); recalc(r);
    if (l == -1) return r;
    if (r == -1) return l;
    if (T[l].y > T[r].y) {
        T[l].r = merge(T[l].r, r);
        recalc(l);
        return l;
    } else {
        T[r].l = merge(l, T[r].l);
        recalc(r);
        return r;
    }
}

// call either with iota-array or whatever you want
pair<int, vi> treap_from_array(vi v) {
    vi nodes(v.size());
    forn(i, v.size()) nodes[i] = create_new_node(v[i]);
    int root = -1; forn(i, v.size()) root = merge(root, nodes[i]);
    return {root, nodes};
}

