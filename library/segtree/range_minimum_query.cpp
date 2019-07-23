#include <bits/stdc++.h>
using namespace std;
#define rep(i,n) for(int i=0; i<(int)(n); i++)
using ll = long long;
using P = pair<ll, ll>;

//
// BEGIN Range minimum query
//

struct {
    int N;
    vector<long long> dat;

    void init(int n) {
      N = 1;
      while(N < n) N *= 2;
      dat.resize(2*N-1, LLONG_MAX);
    }

    // update k-th element
    void update(int k, long long a) {
      k += N-1;
      dat[k] = a;
      while(k > 0) {
        k = (k-1)/2;
        dat[k] = min(dat[k*2+1], dat[k*2+2]);
      }
    }

    // add k-th element by a
    void add(int k, long long a) {
      k += N-1;
      dat[k] += a;
      while(k > 0) {
        k = (k-1)/2;
        dat[k] = min(dat[k*2+1], dat[k*2+2]);
      }
    }

    // return k-th element
    long long get(int k) {
      return dat[k+N-1];
    }

    // return min[a, b)
    long long query(int a, int b) {
      return query(a, b, 0, 0, N);
    }
    long long query(int a, int b, int k, int l, int r) {
      if (r <= a || b <= l) return LLONG_MAX;
      if (a <= l && r <= b) return dat[k];
      int m = (l+r)/2;
      return min(query(a, b, k*2+1, l, m), query(a, b, k*2+2, m, r));
    }
} S;

//
// END range_minimum_query
//

// Verify: https://atcoder.jp/contests/arc085/submissions/6316048

signed main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n; cin >> n;
  S.init(n+1);
  vector<int> b(n);
  int zero = 0;
  rep(i, n) {
    cin >> b[i];
    if (b[i]==0) zero++;
  }
  int q; cin >> q;
  vector<P> ra(q);
  rep(i, q) {
    ll l, r; cin >> l >> r;
    ra[i].first = l;
    ra[i].second = r;
  }
  sort(ra.begin(), ra.end());
  S.update(0, 0);
  int j = 0;
  for(int i=1; i<=n; i++) {
    while(j < q && ra[j].first==i) {
      int l = ra[j].first;
      int r = ra[j].second;
      auto mi = S.query(l-1, r);
      if (mi < S.get(r)) {
        S.update(r, mi);
      }
      j++;
    }
    auto p = (b[i-1]==0) ? -1 : 1;
    auto mi = S.get(i-1)+p;
    if (mi < S.get(i)) {
      S.update(i, mi);
    }
  }
  cout << zero+S.get(n) << endl;
}