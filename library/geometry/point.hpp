double eps = 1e-10;
double add(double a, double b) {
  if (abs(a+b) < eps*(abs(a) + abs(b))) return 0;
  return a+b;
}

struct Point {
    double x, y;
    Point()= default;
    Point(double x, double y) : x(x), y(y) {}
    Point operator+(Point p) { return {add(x, p.x), add(y, p.y)};}
    Point operator-(Point p) { return {add(x, -p.x), add(y, -p.y)};}
    Point operator*(double d) { return {x*d, y*d};}
    double dot(Point p) { return add(x*p.x, y*p.y);}
    double det(Point p) { return add(x*p.y, -y*p.x);}
    // return true if q exists on a line segment [p1, p2]
    static bool on_seg(Point p1, Point p2, Point q) {
      return (p1-q).det(p2-q) == 0 && (p1-q).dot(p2-q) <= 0;
    }
    // return intersection of two lines (p1, p2), (q1, q2)
    static Point intersection(Point p1, Point p2, Point q1, Point q2) {
      return p1 + (p2-p1)*((q2-q1).det(q1-p1)/(q2-q1).det(p2-p1));
    }
};

// return true if the two line segment [p1, p2], [q1, q2] is intersected
static bool is_intersected(Point p1, Point p2, Point q1, Point q2) {
  return (p2-p1).det(q1-p1) * (p2-p1).det(q2-p1) < 0 &&
         (q2-q1).det(p1-q1) * (q2-q1).det(p2-q1) < 0;
}
