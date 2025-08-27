/**
 * Author: David Rydh, Per Austrin
 * Date: 2003-03-16
 * Description:
 */
#pragma once

struct Poly {
	vector<double> a; // a[0] + a[1]x + a[2]x^2 + ...
	void divroot(double x0) { // divide by (x - x0)
		double b = a.back(), c; a.back() = 0;
		for(int i=sz(a)-1; i--;) c = a[i], a[i] = a[i+1]*x0+b, b=c;
		a.pop_back();
	}
};
