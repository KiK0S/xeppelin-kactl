/**
 * Author: isaf27
 * Description: Halfplanes intersection.
 * Time: $O(n \log n)$
 */



namespace hpi {
	const ld eps = 1e-8;
	typedef pair<ld, ld> pi;

	bool z(ld x) { return fabs(x) < eps; }

	ld ccw(pi a, pi b, pi c) {
		return (b.fr - a.fr) * (c.sc - a.sc) - (b.sc - a.sc) * (c.fr - a.fr);
	}

	struct line {
		ld a, b, c;

		bool operator<(const line &l) const {
			bool f1 = pi(a, b) > pi(0, 0);
			bool f2 = pi(l.a, l.b) > pi(0, 0);
			if (f1 != f2) return f1 > f2;
			ld t = ccw(pi(0, 0), pi(a, b), pi(l.a, l.b));
			return z(t) ? c * hypot(l.a, l.b) < l.c * hypot(a, b) : t > 0;
		}

		pi sl() { return pi(a, b); }
	};

	pi cross(line a, line b) {
		ld det = a.a * b.b - b.a * a.b;
		return pi((a.c * b.b - a.b * b.c) / det, (a.a * b.c - a.c * b.a) / det);
	}

	bool bad(line a, line b, line c) {
		if (ccw(pi(0, 0), a.sl(), b.sl()) <= 0) return false;
		pi cs = cross(a, b);
		return cs.first * c.a + cs.second * c.b >= c.c;
	}

	bool solve(vector<line>& v, vector<pi>* solution) { // ax + by <= c;
		sort(v.begin(), v.end());
		deque<line> d;
		for (auto &i: v) {
			if (!d.empty() && z(ccw(pi(0, 0), d.back().sl(), i.sl()))) continue;
			while (d.size() >= 2 && bad(d[d.size() - 2], d.back(), i)) d.pop_back();
			while (d.size() >= 2 && bad(i, d[0], d[1])) d.pop_front();
			d.push_back(i);
		}
		while (d.size() > 2 && bad(d[d.size() - 2], d.back(), d[0])) d.pop_back();
		while (d.size() > 2 && bad(d.back(), d[0], d[1])) d.pop_front();
		if (solution != nullptr) solution->clear();
		for (int i = 0; i < d.size(); i++) {
			line cur = d[i], nxt = d[(i + 1) % d.size()];
			if (ccw(pi(0, 0), cur.sl(), nxt.sl()) <= eps) return false;
			if (solution != nullptr) solution->emplace_back(cross(cur, nxt));
		}
		v = vector<line>(d.begin(), d.end());
		return true;
	}
}

// halfplane of d(p, v1) \le d(p, v2), ax + by <= c
hpi::line nearest(const vect<ll>& v1, const vect<ll>& v2) {
	return hpi::line{
		(ld)((v2.x - v1.x) * 2), (ld)((v2.y - v1.y) * 2),
		(ld)(v2.x * v2.x + v2.y * v2.y - v1.y * v1.y - v1.x * v1.x)
	};
}

// halfplane on the left side of v1v2, ax + by <= c
hpi::line left_side(const vect<ll>& v1, const vect<ll>& v2) {
	return hpi::line{
		(ld)(v2.y - v1.y), (ld)(v1.x - v2.x),
		(ld)(v1.x * v2.y - v2.x * v1.y)
	};
}

const int X = 1e9;

// points should be different !!!
vector<vector<hpi::line>> voronoi(const vector<vect<ll>>& v) {
	vector<vector<hpi::line>> res;
	res.reserve(v.size());
	for (int i = 0; i < (int)v.size(); i++) {
		vector<hpi::line> lines;
		lines.reserve((int)v.size() + 3);
		lines.emplace_back(hpi::line{-1, 0, X});
		lines.emplace_back(hpi::line{1, 0, X});
		lines.emplace_back(hpi::line{0, -1, X});
		lines.emplace_back(hpi::line{0, 1, X});
		for (int j = 0; j < (int)v.size(); j++) {
			if (j != i) {
				lines.emplace_back(nearest(v[i], v[j]));
			}
		}
		hpi::solve(lines, nullptr);
		res.emplace_back(lines);
	}
	return res;
}