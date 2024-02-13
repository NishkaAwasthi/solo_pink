#include <cassert>
#include <iostream>
#include <cmath>
#include <vector>

typedef long long ll;
using namespace std;



int main() {
    int testcases;
    cin >> testcases;

    for (int i = 0; i < testcases; i++) {
        vector<vector<string> > rubiks;

        // Fill in cube
        for (int j = 0; j < 3; j++) {
            vector<string> rubiks_row;
            string temp;
            
            for (int k = 0; k < 18; k++) {
                cin >> temp;
                rubiks_row.push_back(temp);
            }

            rubiks.push_back(rubiks_row);
        }

        // Take in rotation directions
        string instruct;
        cin >> instruct;

        for (char c : instruct) {
            if (c == 'W') {
                string temp1, temp2, temp3;
                temp1 = rubiks[0][3];
                temp2 = rubiks[1][3];
                temp3 = rubiks[2][3];

                rubiks[0][3] = rubiks[0][12];
                rubiks[1][3] = rubiks[1][12];
                rubiks[2][3] = rubiks[2][12];

                rubiks[0][12] = rubiks[0][9];
                rubiks[1][12] = rubiks[1][9];
                rubiks[2][12] = rubiks[2][9];

                rubiks[0][9] = rubiks[0][6];
                rubiks[1][9] = rubiks[1][6];
                rubiks[2][9] = rubiks[2][6];

                rubiks[0][6] = temp1;
                rubiks[1][6] = temp2;
                rubiks[2][6] = temp3;

                temp1 = rubiks[0][0];
                temp2 = rubiks[0][1];

                rubiks[0][0] = rubiks[2][0];
                rubiks[0][1] = rubiks[1][0];

                rubiks[2][0] = rubiks[2][2];
                rubiks[1][0] = rubiks[2][1];

                rubiks[2][2] = rubiks[0][2];
                rubiks[2][1] = rubiks[1][2];

                rubiks[0][2] = temp1;
                rubiks[1][2] = temp2;
            }

            else if (c == 'O') {
                string temp1, temp2, temp3;
                temp1 = rubiks[0][2];
                temp2 = rubiks[1][2];
                temp3 = rubiks[2][2];

                rubiks[0][2] = rubiks[0][6];
                rubiks[1][2] = rubiks[0][7];
                rubiks[2][2] = rubiks[0][8];

                rubiks[0][6] = rubiks[2][17];
                rubiks[0][7] = rubiks[2][16];
                rubiks[0][8] = rubiks[2][15];

                rubiks[2][17] = rubiks[2][14];
                rubiks[2][16] = rubiks[2][13];
                rubiks[2][15] = rubiks[2][12];

                rubiks[2][14] = temp1;
                rubiks[2][13] = temp2;
                rubiks[2][12] = temp3;

                temp1 = rubiks[0][3];
                temp2 = rubiks[0][4];

                rubiks[0][3] = rubiks[2][3];
                rubiks[0][4] = rubiks[1][3];

                rubiks[2][3] = rubiks[2][5];
                rubiks[1][3] = rubiks[2][4];

                rubiks[2][5] = rubiks[0][5];
                rubiks[2][4] = rubiks[1][5];

                rubiks[0][5] = temp1;
                rubiks[1][5] = temp2;
            } 

            else if (c == 'R') {
                string temp1, temp2, temp3;
                temp1 = rubiks[2][0];
                temp2 = rubiks[2][1];
                temp3 = rubiks[2][2];

                rubiks[2][0] = rubiks[0][11];
                rubiks[2][1] = rubiks[0][10];
                rubiks[2][2] = rubiks[0][9];

                rubiks[0][9] = rubiks[0][17];
                rubiks[0][10] = rubiks[1][17];
                rubiks[0][11] = rubiks[2][17];

                rubiks[0][17] = rubiks[2][5];
                rubiks[1][17] = rubiks[2][4];
                rubiks[2][17] = rubiks[2][3];

                rubiks[2][3] = temp1;
                rubiks[2][4] = temp2;
                rubiks[2][5] = temp3;

                temp1 = rubiks[0][6];
                temp2 = rubiks[0][7];

                rubiks[0][6] = rubiks[2][6];
                rubiks[0][7] = rubiks[1][6];

                rubiks[2][6] = rubiks[2][8];
                rubiks[1][6] = rubiks[2][7];

                rubiks[2][8] = rubiks[0][8];
                rubiks[2][7] = rubiks[1][8];

                rubiks[0][8] = temp1;
                rubiks[1][8] = temp2;
            }

            else if (c == 'B') {
                string temp1, temp2, temp3;
                temp1 = rubiks[0][0];
                temp2 = rubiks[1][0];
                temp3 = rubiks[2][0];

                rubiks[0][0] = rubiks[0][14];
                rubiks[1][0] = rubiks[0][13];
                rubiks[2][0] = rubiks[0][12];

                rubiks[0][14] = rubiks[0][17];
                rubiks[0][13] = rubiks[0][16];
                rubiks[0][12] = rubiks[0][15];

                rubiks[0][17] = rubiks[2][6];
                rubiks[0][16] = rubiks[2][7];
                rubiks[0][15] = rubiks[2][8];

                rubiks[2][6] = temp1;
                rubiks[2][7] = temp2;
                rubiks[2][8] = temp3;

                temp1 = rubiks[0][9];
                temp2 = rubiks[0][10];

                rubiks[0][9] = rubiks[2][9];
                rubiks[0][10] = rubiks[1][9];

                rubiks[2][9] = rubiks[2][11];
                rubiks[1][9] = rubiks[2][10];

                rubiks[2][11] = rubiks[0][11];
                rubiks[2][10] = rubiks[1][11];

                rubiks[0][11] = temp1;
                rubiks[1][11] = temp2;
            }

            else if (c == 'G') {
                string temp1, temp2, temp3;
                temp1 = rubiks[0][0];
                temp2 = rubiks[0][1];
                temp3 = rubiks[0][2];

                rubiks[0][0] = rubiks[0][3];
                rubiks[0][1] = rubiks[0][4];
                rubiks[0][2] = rubiks[0][5];

                rubiks[0][3] = rubiks[2][15];
                rubiks[0][4] = rubiks[1][15];
                rubiks[0][5] = rubiks[0][15];

                rubiks[0][15] = rubiks[2][9];
                rubiks[1][15] = rubiks[2][10];
                rubiks[2][15] = rubiks[2][11];

                rubiks[2][11] = temp1;
                rubiks[2][10] = temp2;
                rubiks[2][9] = temp3;

                temp1 = rubiks[0][12];
                temp2 = rubiks[0][13];

                rubiks[0][12] = rubiks[2][12];
                rubiks[0][13] = rubiks[1][12];

                rubiks[2][12] = rubiks[2][14];
                rubiks[1][12] = rubiks[2][13];

                rubiks[2][14] = rubiks[0][14];
                rubiks[2][13] = rubiks[1][14];

                rubiks[0][14] = temp1;
                rubiks[1][14] = temp2;
            }

            else if (c == 'Y') {
                string temp1, temp2, temp3;
                temp1 = rubiks[0][11];
                temp2 = rubiks[1][11];
                temp3 = rubiks[2][11];

                rubiks[0][11] = rubiks[0][14];
                rubiks[1][11] = rubiks[1][14];
                rubiks[2][11] = rubiks[2][14];

                rubiks[0][14] = rubiks[0][5];
                rubiks[1][14] = rubiks[1][5];
                rubiks[2][14] = rubiks[2][5];

                rubiks[0][5] = rubiks[0][8];
                rubiks[1][5] = rubiks[1][8];
                rubiks[2][5] = rubiks[2][8];

                rubiks[0][8] = temp1;
                rubiks[1][8] = temp2;
                rubiks[2][8] = temp3;

                temp1 = rubiks[0][15];
                temp2 = rubiks[0][16];

                rubiks[0][15] = rubiks[2][15];
                rubiks[0][16] = rubiks[1][15];

                rubiks[2][15] = rubiks[2][17];
                rubiks[1][15] = rubiks[2][16];

                rubiks[2][17] = rubiks[0][17];
                rubiks[2][16] = rubiks[1][17];

                rubiks[0][17] = temp1;
                rubiks[1][17] = temp2;
            }
        }

        for (int j = 0; j < 3; j++) {
            
            for (int k = 0; k < 18; k++) {
                cout << rubiks[j][k] << " ";
            }
            cout << "\n";
        }
        
        cout << "===================================\n";
    }

    return 0;
}

