/**
 * Author: aarzhantsev
 * Description: Exponential generating functions utils on polynomials.
 * EGF is defined as $\sum_{i=0}^{\infty} a_i \frac{x^i}{i!}$
 * conv=fft, cut=resize, neg = -x, add = a+b
 */

 vl deriv(const vl &a) {
	vl out(sz(a)-1);
	rep(i,1,sz(a))
	out[i-1] = (ll)i * a[i] % mod;
	return out;
}

vl underiv(const vl &a) {
	vl out(sz(a)+1);
	rep(i,0,sz(a))
	out[i+1] = modpow(i+1,mod-2) * a[i] % mod;
	return out;
}

vl inverse(const vl &a, ll n=-1) {
	if (n == -1)
		n = sz(a);
	if (sz(a) == 1) {
		return {modpow(a[0], mod-2)};
	}

	vl ai(a);
	for (int i = 1; i < sz(ai); i += 2) ai[i] = (mod - ai[i]) % mod;

	vl T = conv(a, ai);
	vl TT((n + 1) / 2);
	for (int i = 0; i < n; i += 2) 
		TT[i / 2] = i < sz(T) ? T[i] : 0;
	TT = inverse(TT, (n + 1) / 2);
	vl TTT(n);
	for (int i = 0; i < n; i += 2)
		TTT[i] = TT[i / 2];
	vl out = conv(ai, TTT);
	out.resize(n);
	return out;
}

vl log(const vl &a, ll n=-1) {
	if (n==-1) n = sz(a);
	vl logpr = conv(cut(deriv(a), n), inverse(a, n));
	logpr.resize(n-1);
	vl out = underiv(logpr);
	out[0] = 0;
	return out;
}

vl exp(const vl &a, ll n=-1) {
	if (n==-1) n = sz(a);
	int lgt = 1;
	vl q = {1};
	while (lgt < n) {
		lgt *= 2;
		vl q_new = conv(q, add(add({1}, cut(a, lgt)), neg(log(q, lgt))));
		q = q_new;
		q.resize(lgt);
	}
	q.resize(n);
	return q;
}

void bell() {
    vl expx(n, 1); // f - factorials
	expx[n-1] = modpow(f[n-1], mod-2);
	for(int i = n - 2; i >= 0; --i)
		expx[i] = expx[i+1] * (i + 1) % mod;

	vl B = exp(add(expx, {-1}), n); // B[i] * f[i] = ith bell number
}




