/**
 * Author: Lukas Polacek, Simon Lindholm
 * Date: 2019-12-26
 * License: CC0
 * Source: folklore
 * Status: tested as part of DirectedMST.h
 */
#pragma once

// for dcp offline: remember updates and perform rollback
void init() {for (int i = 0; i < n; i++) p[i] = i; sz[i] = 1;}
int get(int x) {if (p[x] == x) return x; return p[x] = get(p[x]);}

a = get(a); b = get(b);  (a == b) return;
if (sz[a] > sz[b]) swap(a, b); p[a] = b; sz[b] += sz[a];