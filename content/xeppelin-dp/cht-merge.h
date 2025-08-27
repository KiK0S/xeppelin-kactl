/**
 * Author: kikos
 * Description: CHT with merge and sum
 * Merging just makes 2-pointers and add to new struct
 * Sum takes minkowski sum of lines, storing
*/

struct Line {
	int k, m;

	int operator ()(int x) {return k * x + m;}
	friend Line operator + (Line a, Line b) {return Line{a.k + b.k, a.m + b.m};}
	friend bool operator == (Line a, Line b) {return a.k == b.k && a.m == b.m;}
	friend bool operator < (Line a, Line b) {return a.k < b.k ||  a.k == b.k && a.m < b.m;}
};
struct Lines {
// int shows where the line is optimal
vector<pair<int, Line>> lines;
Lines() {
	lines = {make_pair(-INF, Line{0, 0})};
} 
int get(int x) {
	// or keep track of pointer
	auto it = upper_bound(lines.begin(), lines.end(), make_pair(x, Line()), [&](pair<int, Line> A, pair<int, Line> B) {
		return A.first < B.first;
	});
	--it;
	return x * it->second.k + it->second.m;
}
void add(Line line) {
	while (true) {
		if (lines.size() == 0) {
			lines.push_back({-INF, line});
			break;
		}
		auto [lx, last] = lines.back();
		assert(line.k >= last.k);
		int dk = line.k - last.k;
		int dm = line.m - last.m;
		if (dk == 0) {
			if (dm <= 0) {
				return;
			}
			lines.pop_back();
			continue;
		}
		// dk * x + dm > 0
		// x > -dm / dk
		int nlx;
		if ((-dm) % dk == 0) {
			nlx = -dm / dk + 1;
		} else {
			nlx = (-dm + dk - 1) / dk;
		}
		if (nlx <= lx) {
			lines.pop_back();
		} else {
			lines.push_back({nlx, line});
			break;
		}
	}
}
Lines merge_sum(Lines& other) {
	int aptr = 0, bptr = 0;
	Lines res;
	while(aptr + 1 < lines.size() || bptr + 1 < other.lines.size()) {
		if (aptr + 1 == lines.size()) {
			bptr++;
			res.lines.push_back({other.lines[bptr].F, lines[aptr].S + other.lines[bptr].S});
		} else if (bptr+1 == other.lines.size()) {
			aptr++;
			res.lines.push_back({lines[aptr].F, lines[aptr].S + other.lines[bptr].S});
		} else if (lines[aptr+1].F > other.lines[bptr+1].F) {
			bptr++;
			res.lines.push_back({other.lines[bptr].F, lines[aptr].S + other.lines[bptr].S});
		} else if (lines[aptr+1].F < other.lines[bptr+1].F) {
			aptr++;
			res.lines.push_back({lines[aptr].F, lines[aptr].S + other.lines[bptr].S});
		} else {
			aptr++;
			bptr++;
			res.lines.push_back({lines[aptr].F, lines[aptr].S + other.lines[bptr].S});
		}
	}
	return res;
}
Lines merge_max(Lines& other) {
	int aptr = 0, bptr = 0;
	Lines res;
	while(aptr + 1 < lines.size() || bptr + 1 < other.lines.size()) {
		if (aptr + 1 == lines.size()) {
			bptr++;
			res.add(other.lines[bptr].S);
		} else if (bptr+1 == other.lines.size()) {
			aptr++;
			res.add(lines[aptr].S);
		} else if (lines[aptr+1].S < other.lines[bptr+1].S) {
			aptr++;
			res.add(lines[aptr].S);
		} else {
			bptr++;
			res.add(other.lines[bptr].S);
		}
	}
}
}