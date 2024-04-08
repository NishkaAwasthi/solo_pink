#include <bits/stdc++.h>
#include <algorithm>
#include <iostream>
using namespace std;

vector<int> solve(vector<vector<int>> &puzzle, vector<int> &ans, vector<int> &placed, int nn) {
    if (nn == 7) { return ans; }

    for (int i = 0; i < 7; i++) {
        if (placed[i] == 0) { // not placed
            placed[i] = 1;
            ans[nn] = i;

            std::vector<int> temp = solve(puzzle, ans, placed, nn++);
            if (!temp.empty()) //if not empty
                return temp;

            else {
                placed[i] = 0;
            }
        }
    }
    return vector<int>();
}


void rotate(vector<int> &piece, int pos, int num) {
    int index = find(piece.begin(), piece.end(), num) - piece.begin();
    if (index == pos) return; 

    reverse(piece.begin(), piece.end());
    reverse(piece.begin(), piece.begin() + 6 - pos);
    reverse(piece.begin() + 6 - pos, piece.end());
}

// void rotate(vector<int> &piece, int pos, int num) {
//     while (piece[pos] != num) {
//         int temp = piece[0];
//         for (int i = 1; i < 6; i++) {piece[i-1] = piece[i];}
//         piece[5] = temp;
//     } // can def be optimized
// }

int check(vector<vector<int>> &puzzle, vector<int> &ans) {
    vector<vector<int>> sol(7);
    for (int i = 0; i < 6; i++) {
        sol[i] = puzzle[ans[i]];
    }

    // center is fixed now
    rotate(sol[0], 0, 1);

    //fix side pieces
    int c;
    for (int i = 0; i < 6; i++) {
        if (i < 5) c = i + 2;
        else c = 0;
        rotate(sol[i], c, sol[0][i-1]);
    }

    for (int i = 1; i < 7; i++) {
        int x = i+1;
        if (x >= 7) x = 1;

        int a, b;
        if (i == 6) a = 0;
        else a = i + 1;

        if (i >= 3) b = i - 3;
        else b = i + 4;

        if (sol[i][a] != sol[x][b])
            return 0;
    }
    return 1;
}



int main() {
    int ct;
    cin >> ct;

    vector<vector<int>> puzzle(7, vector<int>(6));
    for (int i = 0; i < ct; i++) {
        // get current puzzle
        for (int j = 0; j < 7; j++) {
            for (int k = 0; k < 6; k++) {
                cin >> puzzle[j][k];
            }
        }
        
        vector<int> ans(7, 0);
        vector<int> placed(7, 0);
        ans = solve(puzzle, ans, placed, 0);
        
        cout << "Case " << i + 1 << ": ";
        if (check(puzzle, ans)) {
            for (int l : ans) {
                cout << l;
            }
            cout << "\n";
        } 
        else { cout << "No Solution\n";}
        
    }
}
