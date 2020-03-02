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
    Point operator/(double d) { return {x/d, y/d};}
    double dot(Point p) { return add(x*p.x, y*p.y);}
    double det(Point p) { return add(x*p.y, -y*p.x);}
    double dist(Point a){return (*this-a).norm();}
    double norm() {return sqrt(x*x+y*y);}
    Point rotate90() { return Point(y, -x);}

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

int sgn(double a, double b=0){return a<b-eps?-1:a>b+eps?1:0;}

struct Circle{
    Point p;
    double r;
    Circle(){}
    Circle(Point p, double r) : p(p) , r(r){}

    bool contain(Point a){
      return sgn((a-p).norm(),r)<=0;
    }

    // Return the minimum circum-circle of the 2 points.
    Circle circumCircle(Point a,Point b){
      Point q=(a+b)/2;
      return Circle(q,(a-q).norm());
    }

    // Return the circum-circle of the 3 points.
    Circle circumscribedCircle(Point p, Point q, Point r){
      Point a=(q-p)*2,b=(r-p)*2;
      Point c(p.dot(p)-q.dot(q),p.dot(p)-r.dot(r));
      Circle res;
      res.p.x=a.y*c.y-b.y*c.x;
      res.p.y=b.x*c.x-a.x*c.y;
      res.p=res.p/a.det(b);
      return Circle(res.p, p.dist(res.p));
    }

    // Return the minimum enclosing circle in O(ps.size()).
    // The input should be shuffled.
    Circle minEnclosingCircle(vector<Point>ps){
      if(ps.size()==0)return Circle(Point(0,0),0);
      if(ps.size()==1)return Circle(ps[0],0);

      Circle circle=circumCircle(ps[0],ps[1]);
      for(int i=2;i<ps.size();i++){
        if(!circle.contain(ps[i])){
          circle=circumCircle(ps[0],ps[i]);
          for(int j=1;j<i;j++){
            if(!circle.contain(ps[j])){
              circle=circumCircle(ps[j],ps[i]);
              for(int k=0;k<j;k++){
                if(!circle.contain(ps[k])){
                  circle=circumscribedCircle(ps[i],ps[j],ps[k]);
                }
              }
            }
          }
        }
      }
      return circle;
    }

    // Return if the two circle is crossed
    static bool crossed(Circle c1, Circle c2) {
      double d = (c1.p-c2.p).norm();
      double rc = (d*d + c1.r*c1.r - c2.r*c2.r) / (2*d);
      return c1.r*c1.r - rc*rc >= 0;
    }

    // Return two cross points. It should be guarded by crossed function.
    static pair<Point, Point> cross(Circle c1, Circle c2) {
      double d = (c1.p-c2.p).norm();
      double rc = (d*d + c1.r*c1.r - c2.r*c2.r) / (2*d);
      double rs = sqrt(c1.r*c1.r - rc*rc);
      Point diff = (c2.p - c1.p) / d;
      Point diff90 = diff.rotate90();
      return make_pair(c1.p + diff*rc + diff90*rs, c1.p + diff*rc - diff90*rs);
    }
};
