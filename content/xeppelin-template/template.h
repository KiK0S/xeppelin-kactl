#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#ifdef DEBUG
#define var(x) cerr << #x << ": " << x << '\n';
#define range(a, b) cerr << #a << ", " << #b << ": "; for (auto _it = a; _it != b; ++_it) cerr << *_it << ' '; cerr << '\n';
#else
#define cerr if (false) cerr
#define var(x)
#define range(a, b)
#endif

#define pii pair<int, int>
#define T(x, i) get<i>(x)
#define F first
#define S second
#define all(v) v.begin(), v.end()
#define forn(i, n) for (int i = 0; i < n; i++)

const int MAXN = 1e6 + 10;
int n;

void solve() {

}

signed main() {
    #ifdef DEBUG
    freopen("input.in", "r", stdin);
    freopen("output.out", "w", stdout);
    #endif
    ios_base::sync_with_stdio(0); cin.tie(0);
    while (cin >> n) solve();
}