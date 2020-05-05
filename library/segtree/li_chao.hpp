// Verified: https://judge.yosupo.jp/submission/8595

/*
 * How to use:

 LiChao<ll, true> seg(h);

 * h: sorted points (where to be queried)
 */
template<typename T, bool isMin>
struct LiChao {

    int N;
    static constexpr T INF = numeric_limits<T>::max();
    struct Line {
        T a, b;
        Line(T a, T b): a(a), b(b){}
        T get(T x){ return a*x + b;}
    };
    vector<T> pos;
    vector<Line> dat;

    LiChao(int n) {
      pos.resize(n);
      for(int i=0; i<n; i++) pos[i] = i;
      init(n);
    }
    LiChao(const vector<T> &pos):pos(pos){init(pos.size());}

    void init(int n) {
      N=1;
      while(N<n) N<<=1;
      while((int)pos.size() < N) {
        pos.emplace_back(T(pos.back())+1);
      }
      dat.resize(2*N, Line(0, -INF));
    }

    // Add ax + b
    void addLine(T a, T b) {
      if (isMin) a = -a, b = -b;
      update(1, 0, N, Line(a, b));
    }

    void update(int k, int l, int r, Line x) {
      T lb = pos[l], ub = pos[r];
      int med = (l + r) / 2;
      if (dat[k].get(pos[med]) < x.get(pos[med])) {
        swap(dat[k], x);
      }
      if (l + 1 == r) return;
      if (x.a < dat[k].a) {
        update(k * 2, l, med, x);
      } else if (x.a > dat[k].a) {
        update(k * 2 + 1, med, r, x);
      }
    }

    T query(T x) {
      auto t = distance(pos.begin(), lower_bound(pos.begin(), pos.end(), x));
      assert(0 <= t && t < (int)pos.size() && pos[t] == x);
      if (isMin) {
        return -query(0, N-1, t);
      } else {
        return query(0, N-1, t);
      }
    }

    T query(int l, int r, int t) {
      T ret = -INF;
      int k = t + N;
      while (k >= 1) {
        ret = max(ret, dat[k].get(pos[t]));
        k >>= 1;
      }
      return ret;
    }

};