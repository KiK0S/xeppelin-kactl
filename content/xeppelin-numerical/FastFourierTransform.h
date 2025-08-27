/**
 * Author: Ludo Pulles, chilli, Simon Lindholm
 * Date: 2019-01-09
 * License: CC0
 * Source: http://neerc.ifmo.ru/trains/toulouse/2017/fft2.pdf (do read, it's excellent)
   Accuracy bound from http://www.daemonology.net/papers/fft.pdf
 * Description: fft(a) computes $\hat f(k) = \sum_x a[x] \exp(2\pi i \cdot k x / N)$ for all $k$. N must be a power of 2.
   For convolution of complex numbers or more than two vectors: FFT, multiply
   pointwise, divide by n, reverse(start+1, end), FFT back.
   Rounding is safe if $(\sum a_i^2 + \sum b_i^2)\log_2{N} < 9\cdot10^{14}$
   (in practice $10^{16}$; higher for random inputs).
 * Time: O(N \log N) with $N = |A|+|B|$ ($\tilde 1s$ for $N=2^{22}$)
 * Status: somewhat tested
 * Details: An in-depth examination of precision for both FFT and FFTMod can be found
 * here (https://github.com/simonlindholm/fft-precision/blob/master/fft-precision.md)
 */
#pragma once

typedef ll cx; // or complex<double>
int MAXLOG = 1;
cx g = 31; // for mod = 998244353, n = 2 ** 23, cx(cos(2 * PI / (1 << MAXLOG)), sin(2 * PI / (1 << MAXLOG))) for doubles
cx gr = modinv(g, mod); // or -g for complex's

// input data, output data, size of input/output view, unity root, start of input view, step of input view, start of output view
inline void fft(vector<cx> &a, vector<cx> &ans, int n, cx z, int abg, int ast, int ansbg) {
	if (n == 1) {
		ans[ansbg] = a[abg];
		return;
	}
	fft(a, ans, n / 2, (z * z) % mod, abg, ast * 2, ansbg);
	fft(a, ans, n / 2, (z * z) % mod, abg + ast, ast * 2, ansbg + n / 2);
	cx x = 1;
	for (int i = 0; i < n / 2; i++) {
		cx ans1 = ans[ansbg + i];
		cx ans2 = ans[ansbg + i + n / 2];
		ans[ansbg + i] = (ans1 + x * ans2) % mod;
		ans[ansbg + i + n / 2] = (ans1 - ((x * ans2) % mod) + mod) % mod;
		x = (x * z) % mod;
	}
}


// careful, this corrupts both a and b!
void multiply(vector<cx> & a, vector<cx> & b) {
	while (2 * max(a.size(), b.size()) > (1 << MAXLOG)) MAXLOG++;
	for (int i = 0; i < (23 - MAXLOG); i++) g = (g * g) % mod;
	a.resize((1 << MAXLOG), 0); b.resize((1 << MAXLOG), 0);
	vector<cx> a_res((1 << MAXLOG), 0);
	fft(a, a_res, 1 << MAXLOG, g, 0, 1, 0);
	fft(b, a, 1 << MAXLOG, g, 0, 1, 0);
	for (int i = 0; i < 1 << MAXLOG; i++) a[i] = (a[i] * a_res[i]) % mod;
	fft(a, b, 1 << MAXLOG, g, 0, 1, 0);
	reverse(b.begin() + 1, b.end());
	cx mp = modinv(1 << MAXLOG, mod);
	for (int i = 0; i < 1 << MAXLOG; i++) b[i] = (b[i] * mp) % mod;
}