/**
 * Author: Ulf Lundstrom
 * Date: 2009-08-03
 * License: CC0
 * Source: My head
 * Description: Basic operations on square matrices.
 * Usage: Matrix<int, 3> A;
 *  A.d = {{{{1,2,3}}, {{4,5,6}}, {{7,8,9}}}};
 *  vector<int> vec = {1,2,3};
 *  vec = (A^N) * vec;
 * Status: tested
 */
#pragma once

vector<vector<int>> multiply(const vector<vector<int>>& a, const vector<vector<int>>& b) {
	int n = a.size(); int m = a[0].size(); int k = b[0].size(); assert(b.size() == m);
	vector<vector<int>> v(k, vector<int>(m)); vector<vector<int>> res(n, vector<int>(k));
	for (int i = 0; i < m; i++) for (int j = 0; j < k; j++) v[j][i] = b[i][j];
	// if using mod, can do MOD^2 by if-ing and taking 1 final mod
	for (int i = 0; i < n; i++) for (int j = 0; j < k; j++) for (int l = 0; l < m; l++) res[i][k] += a[i][l] * v[j][l];
}