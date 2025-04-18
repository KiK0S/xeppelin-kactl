/**
 * Author: algorithmica.org
 * Description: Builds palindrome tree for a string.
*/

int n, last, sz;
// link[v] - longest palindrom suffix of v

void init() {
    s[n++] = -1;
    link[0] = 1;
    len[1] = -1;
    sz = 2;
}

int get_link(int v) {
    while (s[n-len[v]-2] != s[n-1])
        v = link[v];
    return v;
}

void add_char(int c) {
    s[n++] = c;
    last = get_link(last);
    if (!to[last][c]) {
        len[sz] = len[last] + 2;
        link[sz] = to[get_link(link[last])][c];
        to[last][c] = sz++;
    }
    last = to[last][c];
}