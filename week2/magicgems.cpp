#include <bits/stdc++.h>
#include <iostream>
#include <cstdio>

using namespace std;
typedef long long ll;


long long n; // # of gem slots available
long long m; // # of gems a magic gem splits long longo

int MOD = 1000000007;

// Matrix Exponentiation
// Create Kernel Matrix

// how many combinations of filling n slots
    // dp[i] = dp[i-1]    +    dp[i-m]
            // one magic gem, split magic gem

    // 

// Exponentiate to N

// Find sum of diagonals

// Create Kernel Matrix
vector<vector<long long> > create_matrix(long long size) {
    vector<vector<long long> > array(size, vector<long long>(size, 0));

    // Set ones on the diagonals
    for (long long i = 0; i < size; ++i) {
        array[i][i] = 1;
    }
    return array;
}


// Create Kernel Matrix
vector<vector<long long> > create_k_matrix(long long size) {
    vector<vector<long long> > array(size, vector<long long>(size, 0));

    // Set ones on the diagonals
    for (long long i = 1; i < size; ++i) {
        array[i][i-1] = 1;
    }

    array[0][0] = 1;
    array[0][size-1] = 1;

    return array;
}


// Matrix multiplication formula
vector<vector<long long> > matrix_multiply(vector<vector<long long> > &a, vector<vector<long long> > &b) {
    vector<vector<long long> > ans(a.size(), vector<long long>(b[0].size(), 0));

    for (int i = 0; i < a.size(); i++) {
        for (int j = 0; j < b.size(); j++) {
            for (int k = 0; k < b[0].size(); k++) {
                ans[i][k] = (ans[i][k] + ((a[i][j]*b[j][k]) % MOD)) % MOD;
            }
        }
    }

    return ans;
}

// matrix exponentiation
// https://www.hackerearth.com/practice/notes/matrix-exponentiation-1/
vector<vector<long long> > matrix_power(vector<vector<long long> > &a, long long &x) {
    vector<vector<long long> > result = create_matrix(a.size());

    while (x > 0) {
        if ((x % 2) == 1) {
            result = matrix_multiply(result, a);
        }

        a = matrix_multiply(a, a);
        x = x / 2;
    }
  return result;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    long long n, m;
    cin >> n >> m;
    vector<vector<long long> > result = create_k_matrix(m);

    result = matrix_power(result, n);
    cout << result[0][0] << '\n';
}



// long long main() {
//     vector<ll> fact(10);
//     fact[0] = 1;
//     fact[1] = 1;
//     for (ll i = 2; i<fact.size(); i++) {
//         fact[i] = (i * fact[i-1]);
//     }

//     long long n;
//     long long m;
//     cin >> n >> m; 

//     long long recurse(n, m) {
//         long long p = 1;
//         long long ans = 0;
//         while ((p * m) < n) {
//             ans += fact[n-((m-1)*p)]/(fact[n-((m-1)*p) - 1]); 
//             p++;
//         }
//         return ans;
//     }


//     long long ans = 1; // account for ALL magic gems

//     //ans += fact[n-m+1]/(fact[n-m]); //if i only split 1 gem at a time
//     // cout << fact[n-m+1]/(fact[n-m]) << '\n';
//     // cout << fact[n-((m-1)*p)]/(fact[n-((m-1)*p) - 1]) << '\n';

//     //can i have a solution of ALL split gems?
//     if (n % 2 == 0) {
//         ans += 1;
//     }
    
//     recurse(n,m);
//     cout << ans << '\n';

// }
