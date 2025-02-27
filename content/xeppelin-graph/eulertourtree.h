/*
    Euler tour tree. Treap with support for parents
*/

struct node {
    int sz, y, push, depth, l, r, p, pc;
    node(int val = 0) {
        y = rng(); sz = 1;
        push = 0; depth = val;
        l = -1; r = -1; p = -1;}};

node T[MAXN];

int getsz(int v) {
    if (v == -1) return 0;
    return T[v].sz;
}

void push(int v) {
    if (v == -1) return;
    T[v].depth += T[v].push;
    if (T[v].l != -1) T[T[v].l].push += T[v].push;
    if (T[v].r != -1) T[T[v].r].push += T[v].push;
    T[v].push = 0;
}

void recalc(int v) {
    if (v == -1) return;
    T[v].sz = getsz(T[v].l) + getsz(T[v].r) + 1;
    if (T[v].l != -1) {
        T[T[v].l].p = v;
        T[T[v].l].pc = 0;
    }
    if (T[v].r != -1) {
        T[T[v].r].p = v;
        T[T[v].r].pc = 1;
    }
    T[v].p = -1;
}

int pos(int v) {
    int sz = getsz(T[v].l);
    while (v != -1) {
        int pc = T[v].pc;
        v = T[v].p;
        if (pc) sz += getsz(T[v].l) + 1;
    }
    return sz;
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
    push(l);
    push(r);
    recalc(l);
    recalc(r);
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

int root;
int get(int v) {
    int to_cut_l = pos(v);
    auto [L, R] = split(root, to_cut_l);
    int to_cut_r = 1;
    auto p = split(R, to_cut_r);
    int ans = T[p.F].ans;
    R = merge(p.F, p.S);
    root = merge(L, R);
    return ans;
}