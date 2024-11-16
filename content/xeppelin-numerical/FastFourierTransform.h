/**
 * Author: Ludo Pulles, chilli, Simon Lindholm
 * Date: 2019-01-09
 * License: CC0
 * Source: http://neerc.ifmo.ru/trains/toulouse/2017/fft2.pdf (do read, it's excellent)
   Accuracy bound from http://www.daemonology.net/papers/fft.pdf
 * Description: fft(a) computes $\hat f(k) = \sum_x a[x] \exp(2\pi i \cdot k x / N)$ for all $k$. N must be a power of 2.
   Useful for convolution:
   \texttt{conv(a, b) = c}, where $c[x] = \sum a[i]b[x-i]$.
   For convolution of complex numbers or more than two vectors: FFT, multiply
   pointwise, divide by n, reverse(start+1, end), FFT back.
   Rounding is safe if $(\sum a_i^2 + \sum b_i^2)\log_2{N} < 9\cdot10^{14}$
   (in practice $10^{16}$; higher for random inputs).
   Otherwise, use NTT/FFTMod.
 * Time: O(N \log N) with $N = |A|+|B|$ ($\tilde 1s$ for $N=2^{22}$)
 * Status: somewhat tested
 * Details: An in-depth examination of precision for both FFT and FFTMod can be found
 * here (https://github.com/simonlindholm/fft-precision/blob/master/fft-precision.md)
 */
#pragma once

typedef ll cx; // or complex<double>
cx g = 62; // for 998244353, 1.0 for doubles
cx gr = modinv(g, mod);

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
		ans[ansbg + i + n / 2] = (ans1 - (x * ans2) % mod + mod) % mod;
		x = (x * z) % mod;
	}
}

void multiply(vector<cx> &a, vector<cx> &b, vector<cx> &ans) {
	fft(a, a_res, 1 << MAXLOG, g, 0, 1, 0);
	fft(b, b_res, 1 << MAXLOG, g, 0, 1, 0);
	for (int i = 0; i < 1 << MAXLOG; i++) {
		c[i] = (a_res[i] * b_res[i]) % mod;
	}
	fft(c, ans, 1 << MAXLOG, gr, 0, 1, 0);
	cx mp = modinv(1 << MAXLOG, mod);
	for (int i = 0; i < 1 << MAXLOG; i++) {
		ans[i] = (ans[i] * mp) % mod;
	}
}
