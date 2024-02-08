//#include <bits/stdc++.h>
#include <cstdio>
#include <cmath>
#include <iostream>
#include <iomanip>
using namespace std;

//Constants
const double EPS = 1E-5;

// Global Radius Variables
double r1, r2;

// Adaptive Simpson
struct simpson {
	double area (double (*f) (double), double l, double r) { 
		double m = l + (r - l) / 2;
		return (f (l) + 4 * f (m) + f (r)) * (r - l) / 6; 
    }
	double solve (double (*f) (double), double l, double r, double eps, double a) {
		double m = l + (r - l) / 2;
		double left = area (f, l, m), right = area (f, m, r);
		if (fabs (left + right - a) <= 15 * eps) {
            return left + right + (left + right - a) / 15.0;
        }

		return solve (f, l, m, eps / 2, left) + solve (f, m, r, eps / 2, right); 
    }

	double solve (double (*f) (double), double l, double r, double eps) {
		return solve (f, l, r, eps, area (f, l, r)); 
    } 
};

// Define integral function at any given x
double integra(double x) {
    return sqrt(((r2*r2) - (x*x))*((r1*r1)-(x*x)));
}

int main() {
    freopen("twocyl.in", "r", stdin);
    freopen("twocyl.out", "w", stdout);

    double temp1, temp2;
    cin >> temp1 >> temp2;

    if (temp2 > temp1) {
        r1 = temp1;
        r2 = temp2;
    } else {
        r1 = temp2;
        r2 = temp1;
    }
    
    simpson twocyl;
    double ans;
    ans = (twocyl.solve(integra, 0, r1, EPS))*8;

    cout << fixed << setprecision(5) << ans << '\n';
}
