// Segment Tree for query sum[a, b)
template<typename T>
class SegTree {
    using F = function<T(T, T)>;
    int N;
    vector<T> dat;
    const F f;  // merge monoids
    const T ID; // identity

    // RangeSumQuery:
    // auto f = [](ll a, ll b) { return a+b; };
    // auto ID = 0LL;

    // RangeMaximumQuery:
    // auto f = [](ll a, ll b) { return max(a, b); };
    // auto ID = 0LL; (sometimes it should be LLONG_MIN)

    // RangeMinimumQuery:
    // auto f = [](ll a, ll b) { return min(a, b); };
    // auto ID = LLONG_MAX;

    // auto seg = SegTree<ll>(100000, f, ID);
public: SegTree(int n, const F f, const T& ID) : f(f), ID(ID) {
    N = 1;
    while(N < n) N *= 2;
    dat.resize(2*N-1, ID);
  }

public: void build(vector<T>& a) {
    int n = a.size();
    for(int i=0; i<n; i++) dat[i+N-1] = a[i];
    for(int i=N-2; i>=0; i--) dat[i] = f(dat[i*2+1], dat[i*2+2]);
  }

  // update k-th element
public: void update(int k, const T& a) {
    k += N-1;
    dat[k] = a;
    while(k > 0) {
      k = (k-1)/2;
      dat[k] = f(dat[k*2+1], dat[k*2+2]);
    }
  }

  // add k-th element by a
public: void add(int k, const T& a) {
    k += N-1;
    dat[k] = f(dat[k], a);
    while(k > 0) {
      k = (k-1)/2;
      dat[k] = f(dat[k*2+1], dat[k*2+2]);
    }
  }

  // return sum[a, b)
public: T query(int a, int b) {
    return query(a, b, 0, 0, N);
  }
public: T query(int a, int b, int k, int l, int r) {
    if (r <= a || b <= l) return ID;
    if (a <= l && r <= b) return dat[k];
    auto m = (l+r)/2;
    return f(query(a, b, k*2+1, l, m), query(a, b, k*2+2, m, r));
  }
};