#include <bits/stdc++.h>
#include <iostream>
using namespace std;
 
// abbreviated kactl geo
template <class T>
int sgn(T x) { return (x > 0) - (x < 0); }
template <class T>
struct Point {
    typedef Point P;
    T x, y;
    explicit Point(T x = 0, T y = 0) : x(x), y(y) {}
    bool operator<(P p) const { return tie(x, y) < tie(p.x, p.y); }
    bool operator==(P p) const { return tie(x, y) == tie(p.x, p.y); }
    P operator+(P p) const { return P(x + p.x, y + p.y); }
    P operator-(P p) const { return P(x - p.x, y - p.y); }
    P operator*(T d) const { return P(x * d, y * d); }
    P operator/(T d) const { return P(x / d, y / d); }
    T cross(P p) const { return x * p.y - y * p.x; }
    friend ostream& operator<<(ostream& os, P p) {
        return os << "(" << p.x << "," << p.y << ")";
    }
};
 
// kactl polycenter with hacked in area
typedef Point<double> P;
pair<P, double> polygonCenter(const vector<P>& v) {
    P res(0, 0);
    double A = 0;
    for (int i = 0, j = v.size() - 1; i < v.size(); j = i++) {
        res = res + (v[i] + v[j]) * v[j].cross(v[i]);
        A += v[j].cross(v[i]);
    }
    return { res / A / 3, A / 2 };
}
 
int main() {
    int n;
    cin >> n;
    vector<P> poly;
    double anc;
    double lsup = 3000, rsup = -3000;
    for (int i = 0; i < n; i++) {
        P tmp;
        cin >> tmp.x >> tmp.y;
        if (!i) anc = tmp.x;
        if (tmp.y == 0) {
            lsup = min(lsup, tmp.x), rsup = max(rsup, tmp.x);
        }
        poly.push_back(tmp);
    }
 
    auto tmp = polygonCenter(poly);
    double cent = tmp.first.x;
    // average wf not specifying polygon direction
    double area = abs(tmp.second);
 
    // casework time :)
    // we can treat entire polygon as one point with mass = area, and consider weighted average between anchor point and centroid to be exactly at the support bounds.
    // Solving equation we get weight = polygon area * (support.x - centroid.x) / (anchor.x - support.x)
    double eps = 1e-9; // geo.
    // geo boundary garbage
    if (anc == lsup || anc == rsup) {
        if (anc < cent) anc += eps;
        else anc -= eps;
    }
    int ancLoc = (anc < lsup ? 0 : anc > rsup ? 2 : 1); // location of anchor wrt support, 0 is left, 1 is between, 2 is right
 
    // Centroid within support 
    if (cent >= lsup - eps && cent <= rsup + eps) {
        if (ancLoc == 0) {
            // round up
            long long ans = area * (lsup - cent) / (anc - lsup) + 1 - eps;
            if (ans) cout << "0 .. " << ans << endl;
            else cout << "unstable\n";
        } else if (ancLoc == 1) {
            cout << "0 .. inf\n";
        } else {
            long long ans = area * (rsup - cent) / (anc - rsup) + 1 - eps;
            if (ans) cout << "0 .. " << ans << endl;
            else cout << "unstable\n";
        }
    }
 
    // Centroid to right of support
    else if (cent >= rsup + eps) {
        if (ancLoc == 0) {
            long long l = area * (rsup - cent) / (anc - rsup) + eps,
                    r = area * (lsup - cent) / (anc - lsup) + 1 - eps;
            cout << l << " .. " << r << endl;
        } else if (ancLoc == 1) {
            long long ans = area * (rsup - cent) / (anc - rsup) + eps;
            cout << ans << " .. inf" << endl;
        } else {
            cout << "unstable\n";
        }
    }
 
    // Centroid to left of support
    else {
        if (ancLoc == 0) {
            cout << "unstable\n";
        } else if (ancLoc == 1) {
            long long ans = area * (lsup - cent) / (anc - lsup) + eps;
            cout << ans << " .. inf" << endl;
        } else {
            long long l = area * (lsup - cent) / (anc - lsup) + eps,
                    r = area * (rsup - cent) / (anc - rsup) + 1 - eps;
            cout << l << " .. " << r << endl;
        }
    }
}