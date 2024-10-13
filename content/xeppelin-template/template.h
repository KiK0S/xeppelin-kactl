// g++ -fsanitize=bounds -fsanitize=address -fsanitize=address -g -DDEBUG -O2 A.cpp -o A
#include <bits/stdc++.h> using namespace std;
typedef long long ll; const int MAXN = 4e5;
#ifndef DEBUG #define cerr if(false) cerr #endif
int n; void solve() {}
signed main() { ios_base::sync_with_stdio(0); cin.tie(0);
#ifdef DEBUG freopen("input.txt", "r", stdin);
freopen("output.txt", "w", stdout); #endif
while (cin >> n) solve();}