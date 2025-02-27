/**
 * Author: Lukas Polacek
 * Date: 2009-09-28
 * License: CC0
 * Source: folklore
 * Description: Operators for modular arithmetic.
 */
#pragma once

const ll mod = 17; // change to something else
struct xet {
	int val;
	explicit operator int() const { return val; }
	xet(ll x = 0) { val = (x >= -mod && x < mod ? x : x % mod); if (val < 0) val += mod; }
	xet(ll a, ll b) { *this += a; *this /= b; }
	xet& operator+=(xet const &b) { val += b.val; if (val >= mod) val -= mod; return *this; }
	xet& operator-=(xet const &b) { val -= b.val; if (val < 0) val += mod; return *this; }
	xet& operator*=(xet const &b) { val = (val * (ll)b.val) % mod; return *this; }
	friend xet mypow(xet a, ll n) {
		xet res = 1;
		while (n) { if (n & 1) res *= a; a *= a; n >>= 1; }
		return res;
	}
	friend xet inv(xet a) { return mypow(a, mod - 2); }
	xet& operator/=(xet const& b) { return *this *= inv(b); }
	friend xet operator+(xet a, const xet &b) { return a += b; }
	friend xet operator-(xet a, const xet &b) { return a -= b; }
	friend xet operator-(xet a) { return 0 - a; }
	friend xet operator*(xet a, const xet &b) { return a *= b; }
	friend xet operator/(xet a, const xet &b) { return a /= b; }
	friend bool operator==(xet const &a, xet const &b) { return a.val == b.val; }
	friend bool operator!=(xet const &a, xet const &b) { return a.val != b.val; }
	friend bool operator<(xet const &a, xet const &b) { return a.val < b.val; }

	friend istream& operator>>(istream& stream, xet &a) { return stream >> a.val; }
	friend ostream& operator<<(ostream& stream, const xet &a) { return stream << a.val; }
};
