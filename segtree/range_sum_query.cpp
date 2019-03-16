#include<vector>
using namespace std;

// Segment Tree for query sum[a, b)
struct {
  int N;
  vector<ll> dat;

  void init(int n) {
    N = 1;
    while(N < n) N *= 2;
    dat.resize(2*N-1, 0);
  }

  void build(vector<ll>& a) {
    int n = a.size();
    init(n);
    for(int i=0; i<n; i++) dat[i+N-1] = a[i];
    for(int i=N-2; i>=0; i--) dat[i] = dat[i*2+1]+dat[i*2+2];
  }

  // update k-th element
  void update(int k, long long a) {
    k += N-1;
    dat[k] = a;
    while(k > 0) {
      k = (k-1)/2;
      dat[k] = dat[k*2+1] + dat[k*2+2];
    }
  }

  // add k-th element by a
  void add(int k, long long a) {
    k += N-1;
    dat[k] += a;
    while(k > 0) {
      k = (k-1)/2;
      dat[k] = dat[k*2+1] + dat[k*2+2];
    }
  }

  // return sum[a, b)
  ll query(int a, int b) {
    return query(a, b, 0, 0, N);
  }
  ll query(int a, int b, int k, int l, int r) {
    if (r <= a || b <= l) return 0;
    if (a <= l && r <= b) return dat[k];
    auto m = (l+r)/2;
    return query(a, b, k*2+1, l, m) + query(a, b, k*2+2, m, r);
  }
};