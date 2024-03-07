#include <bits/stdc++.h>
#include <iostream>
#include <iomanip>

#define endl "\n"
#define PI 3.141592

using namespace std;

#define cd const double &
const double EPS = 1E-10;
int sgn (cd x) { return x < -EPS ? -1 : x > EPS; }
int cmp (cd x, cd y) { return sgn (x - y); }
double sqr (cd x) { return x * x; }
double msqrt (cd x) { return sgn (x) <= 0 ? 0 : sqrt (x); }

#define cp const point &
struct point {
	double x, y;
	explicit point (cd x = 0, cd y = 0) : x (x), y (y) {}
	int dim () const { return sgn (y) == 0 ? sgn (x) > 0 : sgn (y) > 0; }
	point unit () const { double l = msqrt (x * x + y * y); return point (x / l, y / l); }
	point rot90 () const { return point (-y, x); }
	point _rot90 () const { return point (y, -x); }
	point rot (cd t) const {
		double c = cos (t), s = sin (t);
		return point (x * c - y * s, x * s + y * c); } };
bool operator == (cp a, cp b) { return cmp (a.x, b.x) == 0 && cmp (a.y, b.y) == 0; }
bool operator != (cp a, cp b) { return cmp (a.x, b.x) != 0 || cmp (a.y, b.y) != 0; }
bool operator < (cp a, cp b) { return cmp (a.x, b.x) == 0 ? cmp (a.y, b.y) < 0 : cmp (a.x, b.x) < 0; }
point operator - (cp a) { return point (-a.x, -a.y); }
point operator + (cp a, cp b) { return point (a.x + b.x, a.y + b.y); }
point operator - (cp a, cp b) { return point (a.x - b.x, a.y - b.y); }
point operator * (cp a, cd b) { return point (a.x * b, a.y * b); }
point operator / (cp a, cd b) { return point (a.x / b, a.y / b); }
double dot (cp a, cp b) { return a.x * b.x + a.y * b.y; }
double det (cp a, cp b) { return a.x * b.y - a.y * b.x; }
double dis2 (cp a, cp b = point ()) { return sqr (a.x - b.x) + sqr (a.y - b.y); }
double dis (cp a, cp b = point ()) { return msqrt (dis2 (a, b)); }

#define cl const line &
struct line {
	point s, t;
	explicit line (cp s = point (), cp t = point ()) : s (s), t (t) {} };
bool point_on_segment (cp a, cl b) { return sgn (det (a - b.s, b.t - b.s)) == 0 && sgn (dot (b.s - a, b.t - a)) <= 0; }
point line_intersect (cl a, cl b) {
	double s1 = det (a.t - a.s, b.s - a.s), s2 = det (a.t - a.s, b.t - a.s);
	return (b.s * s2 - b.t * s1) / (s2 - s1); }
double point_to_line (cp a, cl b) { return std::abs (det (b.t - b.s, a - b.s)) / dis (b.s, b.t); }
point project_to_line (cp a, cl b) { return b.s + (b.t - b.s) * (dot (a - b.s, b.t - b.s) / dis2 (b.t, b.s)); }
double point_to_segment (cp a, cl b) {
	if (sgn (dot (b.s - a, b.t - b.s) * dot (b.t - a, b.t - b.s)) <= 0) return std::abs (det (b.t - b.s, a - b.s)) / dis (b.s, b.t);
	return std::min (dis (a, b.s), dis (a, b.t)); }

#define cc const circle &
struct circle {
	point c; double r;
	explicit circle (point c = point (), double r = 0) : c (c), r (r) {} };
bool operator == (cc a, cc b) { return a.c == b.c && cmp (a.r, b.r) == 0; }
bool operator != (cc a, cc b) { return !(a == b); }
bool in_circle (cp a, cc b) { return cmp (dis (a, b.c), b.r) <= 0; }
circle make_circle (cp a, cp b) { return circle ((a + b) / 2, dis (a, b) / 2); }
std::vector <point> line_circle_intersect (cl a, cc b) {
	if (cmp (point_to_line (b.c, a), b.r) > 0) return std::vector <point> ();
	double x = msqrt (sqr (b.r) - sqr (point_to_line (b.c, a)));
	point s = project_to_line (b.c, a), u = (a.t - a.s).unit ();
	if (sgn (x) == 0) return std::vector <point> ({s});
	return std::vector <point> ({s - u * x, s + u * x}); }

//###############################################################################
//###############################################################################
//###############################################################################xf

int w, l, r, x1, yy1, x2, y2, x3, y3, h;
 
void checkpt(point p) {
    if (p.x < 0 || p.x > w || p.y < 0 || p.y > l) {
        cout << "impossible" << endl;
        exit(0);
    }
}

void checkcircle(line l, point ball) {
    point norm = (l.t-l.s).rot90().unit()*r;
    
    line l1 = line(l.s+norm,l.t+norm);
    line l2 = line(l.s-norm,l.t-norm);

    vector<point> check1 = line_circle_intersect(l1, circle(ball, r));
    vector<point> check2 = line_circle_intersect(l2, circle(ball, r));
    
    for (point p : check1) {
        if (point_on_segment(p, l1) ) {
            cout << "impossible" << endl;
            exit(0);
        }
    }
    for (point p : check2) {
        if (point_on_segment(p, l2) ) {
            cout << "impossible" << endl;
            exit(0);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
	cin.tie(NULL);
    cin >> w >> l >> r >> x1 >> yy1 >> x2 >> y2 >> x3 >> y3 >> h;

    point goalright = point(w,l);
    point goalleft = point(0,l);

    point ball1 = point(x1,yy1);
    point ball2 = point(x2, y2);
    point ball3 = point(x3, y3);

    point goalto3 = ball3 - goalright;
    point col13 = ball3 + goalto3.unit() * (2 * r);

    point goalto2 = ball2 - goalleft;
    point col12 = ball2 + goalto2.unit() * (2 * r);

    point rightto1 = ball1 - col13;
    point firstcol = rightto1.unit() * (2 * r) + ball1;

    point temp = project_to_line(col12, line(firstcol, ball1));
    point reflecttemp = temp + (temp - col12);
    line cueto1 = line (firstcol, reflecttemp);

    checkpt(firstcol);
    checkpt(col13);
    checkpt(col12);
   
    line starting_line = line(point(0,h), point(1,h));
    point cueball = line_intersect(cueto1, starting_line);
 
    checkcircle(line(col13, ball1), ball2);
    checkcircle(line(col12, firstcol), ball3);
    checkcircle(line(col13, goalright), ball2);
    checkcircle(line(col12, goalleft), ball3);
    checkcircle(line(cueball, firstcol), ball2);
    checkcircle(line(cueball, firstcol), ball3);

    if (cueball.x < r || cueball.x > w-r) {
        cout << "impossible" << endl;
    } else {
        point incomingAngle = firstcol - reflecttemp;
        double angle = atan2(incomingAngle.y, incomingAngle.x) * 180 / PI;
        cout << fixed << setprecision(2) << cueball.x << " " << angle << endl;
    }
}

