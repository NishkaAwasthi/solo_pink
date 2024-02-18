#include <iostream>
#include <unordered_set>
#include <bits/stdc++.h>

using namespace std;

const int N = 50 + 5;
const int K = 35000 + 5;
const int nINF = -50000;
int a[N];
int dp[N][K];

int value(int k, int j) {
    unordered_set<int> uniqueValues;
    for (int i = k; i < j+1; i++) {
        uniqueValues.insert(a[i]);
    }
    return uniqueValues.size();
}

int recurse(int boxes, int cakes) {
    if (dp[boxes][cakes] != -1) { 
        return dp[boxes][cakes]; 
    }

     //only one cake and many boxes
    if (cakes == 0 && boxes > 0) {
        dp[boxes][cakes] = nINF;
    }
    
    // only one box
    else if (boxes == 0) {
        dp[boxes][cakes] = value(0, cakes);
    }

    else if (boxes > 0) {   
        //dp[i][j] = max(dp[i-1][k]) + value(k+1, j)
        for (int k = 0; k < cakes+1; k++) {
            dp[boxes][cakes] = max(dp[boxes][cakes], recurse(boxes-1, k) + value(k+1, cakes));
        }
    }
    return dp[boxes][cakes];
}

int main() {
    // get input
    int boxes, cakes;
    cin >> cakes >> boxes;

    for (int i = 0; i <= cakes - 1; i++) { 
        cin >> a[i]; 
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < K; j++) {
            dp[i][j] = -1;
        }
    } 

    cout << recurse(boxes - 1, cakes - 1) << "\n";

    // for (int i = 0; i < boxes; i++) {
    //     for (int j = 0; j < cakes; j++) {
    //         cout << dp[i][j] << " ";
    //     }
    //     cout << "\n";
    // }
}
