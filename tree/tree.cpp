// https://codeforces.com/group/S59XkO4RGq/contest/492194/problem/C

#include <bits/stdc++.h>
#include <algorithm>
#include <iostream>
#include <queue>

using namespace std;
const int maxn = 1000005;
int n, p;

vector<vector<int>> adj; // adjacency
vector<int> dp(n + 1, 0); // max depth
vector<int> pars(n + 1, 0); // max depth
vector<int> deepcc(n + 1, -1); // deepest child 

// int rec(int nn, int prev) {
//     if (adj[nn].size() == 0) return dp[nn] = 1;
//     int mx = 0;
//     for (auto cc : adj[nn]) mx = max(mx, rec(cc)); 
//     if (adj[nn].size() == 1) dp[nn] = mx;
//     else dp[nn] = mx + 1;
//     return dp[nn];
// }

void rec(int nn, int par) {
    pars[nn] = par;
    if (adj[nn].size() == 1) return;
    int mx = -1, deep = -1;
    for (auto cc : adj[nn]) 
        if (cc != par) {
            rec(cc, nn);
            if (dp[cc] > mx) 
                mx = dp[cc]; deep = cc;   
        }
    dp[nn] = mx + 1;
    deepcc[nn] = deep;
}
 
void solve() {
    cin >> n;

    adj.clear(); dp.clear();
    adj.resize(n + 1); dp.resize(n + 1);

    // populate adjacency list
    for (int i = 2; i <= n; ++i) {
        cin >> p;
        adj[p].push_back(i);
        adj[i].push_back(p);
    }

    rec(1, 0);

    int g = dp[1] + 1;
    int ch = 0; 

    // remove biggest chains
    priority_queue <pair<int, int>> prioq; 
    prioq.push({dp[1], 1}); // root
    while (!prioq.empty()) {
        int a, b;
        a = prioq.top().first;
        b = prioq.top().second;
        prioq.pop();

        g = min(g, a + ch + 1);

        while (b != -1) {
            for (auto cc : adj[b]) 
                if (deepcc[b] != cc && pars[b] != cc) prioq.push({dp[cc], cc});
            b = deepcc[b];
        }
        ch++;
    }

    cout << min(ch, g) << endl;
}
 
int main() {
    int t; cin >> t;
    while (t--) solve();
}