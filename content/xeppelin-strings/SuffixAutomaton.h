/**
 * Author: grphil
 * Description: Builds suffix automaton for a string. For a suffix tree give a reversed string and take tree of suflinks. if debugging, use aabab
 * Time: O(n)
 */

struct node {
  int link = -1, p = -1, len = 0;
  char pc = '#'; map<char, int> next;
}; node v[2 * MAXN];

int add_char(int ls, char c) {
  if (v[ls].next.find(c) != v[ls].end()) return v[ls].next[c];
  v[++mx] = node(ls, v[ls].len + 1, c);
  int p = ls;
  for (; p != -1 && v[p].next.find(c) == v[p].end(); p = v[p].link)
      v[p].next[c] = mx;
  if (p == -1) {
      v[mx].link = 0;
      return mx;
  }
  int q = v[p].next[c];
  if (v[q].p == p) {
      v[mx].link = q;
      return mx;
  }
  v[++mx] = node(p, v[p].len + 1, c);
  v[mx].next = v[q].next; v[mx].link = v[q].link;
  v[q].link = v[mx - 1].link = mx;
  for (; p != -1 && v[p].next[c] == q; p = v[p].link)
      v[p].next[c] = mx;
  return mx - 1;
}

void subautomaton(int x, int tm) {
  if (x == -1 || used[x] == tm) return;

  used[x] = tm;
  //....

  subautomaton(v[x].p, tm);
  subautomaton(v[x].link, tm);
}