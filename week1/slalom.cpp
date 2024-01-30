#include <cassert>
#include <iostream>
#include <cmath>

#define cd const double &
const double EPS = 1E-8, PI = acos (-1); 
int sgn (cd x) { return x < -EPS ? -1 : x > EPS; }
int cmp (cd x, cd y) { return sgn (x - y); }
double sqr (cd x) { return x * x; }
double msqrt (cd x) { return sgn (x) <= 0 ? 0 : sqrt (x); }

#define cp const point &
struct point {
	double x, y;
	explicit point (cd x = 0, cd y = 0) : x (x), y (y) {} 
};
point operator - (cp a, cp b) { return point (a.x - b.x, a.y - b.y); }
point operator * (cp a, cd b) { return point (a.x * b, a.y * b); }
point operator / (cp a, cd b) { return point (a.x / b, a.y / b); }


double dot (cp a, cp b) {return a.x * b.x + a.y * b.y; }
double det (cp a, cp b) {return a.x * b.y - a.y * b.x; }
double dis2 (cp a, cp b = point ()) { return sqr (a.x - b.x) + sqr(a.y - b.y); }
double dis (cp a, cp b = point()) { return msqrt (dis2(a,b)); }

#define cl const line &
struct line {
	point s, t;
	explicit line (cp s = point (), cp t = point ()) : s (s), t (t) {} 
};

bool point_on_segment (cp a, cl b) { return sgn (det (a - b.s, b.t - b.s)) == 0 && sgn (dot (b.s - a, b.t - a)) <= 0; }
point line_intersect (cl a, cl b) {
	double s1 = det (a.t - a.s, b.s - a.s), s2 = det (a.t - a.s, b.t - a.s);
	return (b.s * s2 - b.t * s1) / (s2 - s1); }
double point_to_line (cp a, cl b) { return std::abs (det (b.t - b.s, a - b.s)) / dis (b.s, b.t); }
double point_to_segment (cp a, cl b) {
	if (sgn (dot (b.s - a, b.t - b.s) * dot (b.t - a, b.t - b.s)) <= 0) return std::abs (det (b.t - b.s, a - b.s)) / dis (b.s, b.t);
	return std::min (dis (a, b.s), dis (a, b.t)); 
}

// function to check if segment intersect
bool goes_through_gate (cl a, cl gate) {
    cp p = line_intersect(a, gate);
    return point_on_segment (p, gate);
}

// given a point, what are the two lines
void two_rays (cp a, cl b, line & lineLeft, line & lineRight) { 
    lineLeft = line(a, b.s);
    lineRight = line(a, b.t);
}

// given some y, what are the points that rays intersect
point y_points (cl ray, cd y) {
    line y_line = line(point(0, y), point(1, y));
    return line_intersect(ray, y_line);
}

using namespace std;
int main() {
    int num_gates;
    cin >> num_gates; // number of gates

    double startX, startY;
    cin >> startX >> startY;
    point root = point(startX, startY);
    
    vector<line> gates;
    for(int i = 0; i<num_gates; i++) {
        double y, lineX1, lineX2;
        cin >> y >> lineX1 >> lineX2;
        gates.push_back(line(point(lineX1, y), point(lineX2, y)));
    }

    int root_index = 0;
    float ans = 0;

    line lL;
    line lR;
    two_rays(root, gates[root_index], lL, lR);
    
    for(int i = 1; i < num_gates; i++) {
        line prev_gate = gates[i-1];
        line current_gate = gates[i];
    
        // get leftpoint and rightpoint
        point pL = y_points(lL, prev_gate.s.y);
        point pR = y_points(lR, prev_gate.s.y);

        // check if pL is in range and pR is in range
        if (pL.x > current_gate.s.x && pR.x < current_gate.t.x) {
            // make bounds more strict
            two_rays(root, current_gate, lL, lR);
        }
        else if (pL.x < current_gate.s.x && pR.x < current_gate.t.x) {
            // change right line
            lR = line(current_gate.t, root);
        }
        else if (pL.x > current_gate.s.x && pR.x < current_gate.t.x) {
            // change left line
            lL = line(current_gate.s, root);
        }
        else if (pL.x > current_gate.t.x) {
            // out of bounds right -> new root
            ans += dis(root, prev_gate.t);
            root = prev_gate.t;
            two_rays(root, current_gate, lL, lR);
        }
        else if (pR.x < current_gate.s.x) {
            // out of bounds left -> new root
            ans += dis(root, prev_gate.s);
            root = prev_gate.s;
            two_rays(root, current_gate, lL, lR);
        }
    }
    // at last gate
    float temp1 = dis(root, gates[gates.size() - 1].s);
    float temp2 = dis(root, gates[gates.size() - 1].t);
    float temp3 = dis(root, point(root.x, gates[gates.size() - 1].s.y));

    if (root.x > gates[gates.size() - 1].t.x || root.x < gates[gates.size() - 1].s.x) {
        temp3 = numeric_limits<float>::infinity();
    }
    cout << ans << "\n";
    if (temp1 <= temp2 && temp1 <= temp3) {
        ans += temp1;
    }
    else if (temp2 <= temp1 && temp2 <= temp3) {
        ans += temp2;
    }
    else ans += temp3;

    cout << ans << "\n";

}
    
    
