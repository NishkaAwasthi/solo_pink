// https://codeforces.com/gym/103536/problem/A
#include <cassert>
#include <iostream>
#include <cmath>
typedef long long ll;
using namespace std;

int m, n;
vector<ll> dp_before, dp_cur;

int costs[10000];

ll C(int k, int j) {
    ll tot;
    for (int i = k; i < j; i++) {
        tot += costs[i];
    }
    return tot * (k - j);
}

// compute dp_cur[l], ... dp_cur[r] (inclusive)
void compute(int l, int r, int optl, int optr) {
    if (l > r)
        return;

    int mid = (l + r) >> 1;
    pair<ll, int> best(LLONG_MAX, -1);

    for (int k = optl; k <= min(mid, optr); k++) {
        best = min(best, make_pair((k ? dp_before[k - 1] : 0) + C(k, mid), k));
    }

    dp_cur[mid] = best.first;
    int opt = best.second;

    compute(l, mid - 1, optl, opt);
    compute(mid + 1, r, opt, optr);
}

ll solve() {
    dp_before.assign(n,0);
    dp_cur.assign(n,0);

    for (int i = 0; i < n; i++)
        dp_before[i] = C(0, i);

    for (int i = 1; i < m; i++) {
        compute(0, n - 1, 0, n - 1);
        dp_before = dp_cur;
    }

    return dp_before[n - 1];
}

int main() {
    int n, g;
    cin >> n >> g;

    for (int i = 0; i < n; i++) {
        cin >> costs[i];
    }
 
    cout << solve() << '\n';
}
