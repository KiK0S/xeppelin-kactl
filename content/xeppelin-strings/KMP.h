/**
 * Author: Johan Sannemo
 * Description: pi[x] = the length of the longest prefix of s that ends at x,
 * other than s[0...x] itself (abacaba -> 0010123).
 */
#pragma once

vector<int> p(s.size());
for (int i = 1; i < s.size(); i++) {
	int g = p[i-1];
	while (g && s[i] != s[g]) g = p[g-1];
	p[i] = g + (s[i] == s[g]);     }
