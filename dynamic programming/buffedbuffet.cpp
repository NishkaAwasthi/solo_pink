#include <cassert>
#include <iostream>
#include <cmath>
typedef long long ll;
typedef double d;
using namespace std;

//Constants
const double EPS = 1E-5;

struct simpson {
    d area (d (*f) (d), d l, d r) {
        d m = l + (r - l) / 2;
        return (f(l) + 4 * f(m) + f(r)) * (r - l) / 6; 
    }

    d solve ( d (*f) (d), d l, d r, d eps, d a) {
        d m = l + (r - l) / 2;
        d left = area(f, l, m), right = area(f, m, r);
        if (fabs (left + right - a) <= 15 * eps) {
            return left + right + (left + right - a) / 15.0;
        }
        return solve (f, l, m, eps/2, left) + solve(f, m, r, eps/2, right);
    }
    
    d solve (d (*f) (d), d l, d r, d eps) {
        return solve(f, l , r, eps, area(f, l, r)); 
    }
};

// Global Radius Variables
d t[];
d k[];

//Constants
const d EPS = 1E-5;
d x;

// Define integral function at any given x
d ingr(d x, int i) {
    return sqrt(t[i] - (x*k[i]));
}
int main() {
    d o;
    cin >> o;
    simpson calc;
    //calc.solve(ingr, 0.0, x, EPS)
}