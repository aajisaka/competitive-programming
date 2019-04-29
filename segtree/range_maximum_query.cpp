#include<vector>
using namespace std;

// Segment Tree for query max[a, b)
struct {
  int N;
  vector<long long> dat;

  void init(int n) {
    N = 1;
    while(N < n) N *= 2;
    dat.resize(2*N-1, 0);
  }

  // update k-th element
  void update(int k, long long a) {
    k += N-1;
    dat[k] = a;
    while(k > 0) {
      k = (k-1)/2;
      dat[k] = max(dat[k*2+1], dat[k*2+2]);
    }
  }

  // add k-th element by a
  void add(int k, long long a) {
    k += N-1;
    dat[k] += a;
    while(k > 0) {
      k = (k-1)/2;
      dat[k] = max(dat[k*2+1], dat[k*2+2]);
    }
  }

  // return max[a, b)
  long long query(int a, int b) {
    return query(a, b, 0, 0, N);
  }
  long long query(int a, int b, int k, int l, int r) {
    if (r <= a || b <= l) return 0;
    if (a <= l && r <= b) return dat[k];
    int m = (l+r)/2;
    return max(query(a, b, k*2+1, l, m), query(a, b, k*2+2, m, r));
  }
};