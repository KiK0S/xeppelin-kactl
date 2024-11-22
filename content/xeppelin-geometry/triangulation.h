/**
 * Author: isaf27
 * Description: Triangulation of polygon.
 * Time: idk
 */

// polygon must be given counterclockwise (can be checked with signed area), points must be different !!!
vector<tuple<int, int, int>> triangulation(const vector<vect<ll>> &v) {
	vector<tuple<int, int, int>> ans;
	int n = v.size();
	vector<bool> used(n, false);
	queue<int> all;
	for (int i = 0; i < n; i++) all.push(i);
	for (int iter = 0; iter < n - 2; iter++) {
		while (true) {
			if (all.empty()) return ans;
			int p = all.front();
			all.pop();
			if (used[p]) continue;
			int x = (p + n - 1) % n;
			while (used[x]) x = (x + n - 1) % n;
			int y = p;
			int z = (p + 1) % n;
			while (used[z]) z = (z + 1) % n;
			if (((v[x] - v[y]) ^ (v[z] - v[y])) >= 0) continue;
			bool bad = false;
			for (int i = 0; i < n; i++) {
				if (!used[i] && i != x && i != y && i != z) {
					if (area(v[x], v[y], v[z]) ==
						area(v[x], v[y], v[i]) + area(v[x], v[z], v[i]) + area(v[z], v[y], v[i])) {
						bad = true;
						break;
					}
				}
			}
			if (bad) continue;
			ans.emplace_back(x, y, z);
			used[y] = true;
			all.push(x);
			all.push(z);
			break;
		}
	}
	return ans;
}