// #include <bits/stdc++.h>
#include <iostream>
using namespace std;
typedef long long ll;

int main() {
    vector<ll> fact(25);
    fact[0] = 1;
    fact[1] = 1;
    for (ll i = 2; i<fact.size(); i++) {
        fact[i] = (i * fact[i-1]);
    }

    int num_cases;
    cin >> num_cases;

    for(int i = 0; i<num_cases; i++) {
        int not_in;
        cin >> not_in;
        
        vector<int> useless(not_in);
        int temp;
        for (int i = 0; i<not_in; i++) {
            cin >> temp;
        }

        int n = 10 - not_in;

        ll ans = ((fact[n])/((fact[2])*(fact[n-2]))) * 6;
        cout << ans << '\n';
    }
}
