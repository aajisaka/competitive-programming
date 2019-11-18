// update by range, query by point
class RangeUpdateQuery {
  int N;
  vector<long long> dat;

public: RangeUpdateQuery(int n) {
    N = 1;
    while(N < n) N *= 2;
    dat.resize(2*N-1, 0);
  }

  // add [a, b) by x
public: void add(int a, int b, long long x) {
    return add(a, b, x, 0, 0, N);
  }
  void add(int a, int b, ll x, int k, int l, int r) {
    if (r <= a || b <= l) return;
    if (a <= l && r <= b) {
      dat[k] += x;
      return;
    }
    int m = (l+r)/2;
    add(a, b, x, k*2+1, l, m);
    add(a, b, x, k*2+2, m, r);
  }

  // return k
public: long long query(int k) {
    k += N-1;
    ll ret = dat[k];
    while(k > 0) {
      k = (k-1)/2;
      ret += dat[k];
    }
    return ret;
  }
};