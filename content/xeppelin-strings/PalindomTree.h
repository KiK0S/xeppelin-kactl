/**
 * Author: algorithmica.org
 * Description: Builds palindrome tree for a string.
 * Usage: add_char(str[i]); int v = last; then use len[v], v = link[v]
*/

void init() {
	n = 0;
	last = 0;
	sz = 2;
	s[n++] = -1;       // special character to avoid edge cases
	link[0] = 1;       // imaginary root
	len[0] = 0;        // empty string
	len[1] = -1;       // imaginary string of length -1
	link[1] = 1;       // self-link for imaginary root
}

int get_link(int v) {
	// Find the longest palindromic suffix that can be extended
	while (s[n-len[v]-2] != s[n-1])
		v = link[v];
	return v;
}

void add_char(int c) {
	s[n++] = c;
	last = get_link(last);
	if (!to[last][c]) {	 // new vertex if transition doesn't exist
		len[sz] = len[last] + 2;  // new palindrome length
		link[sz] = to[get_link(link[last])][c];  // find suffix link
		to[last][c] = sz++;
	}
	last = to[last][c];
}