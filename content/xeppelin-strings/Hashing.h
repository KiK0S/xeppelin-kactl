/**
 * Author: kik0s
 * Description: use base 10 for debug if needed
 * Status: stress-tested
 */
#pragma once

int tpow[MAXN]; int h[MAXN]; int t = 179;
tpow[0] = 1; for (int i = 1; i < MAXN; i++) (tpow[i] = 1ll * t * tpow[i - 1]) % MOD;
for (int i = 0; i < n; i++) {
	h[i] = (1ll * (i == 0 ? 0: h[i - 1]) * t + s[i] - 'a' + 1) % MOD;}
int get_hash(int l, int r) {
	if (!l) return h[r];
	return (1ll * MOD + hpow[r] - (1ll * hpow[l - 1] * tpow[r - l + 1]) % MOD) % MOD;}