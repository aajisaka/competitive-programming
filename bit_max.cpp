#include <algorithm>
#include <vector>

using ll = long long;
using namespace std;

struct {
  int MAXN; vector<ll> bit;

  void init(int n) {
    MAXN = n;
    bit.resize(n+1);
  }

  // update bit[j] (j >= i > 0) with max(bit[j], x)
  void update(int i, ll x) {
    while (i <= MAXN) {
      bit.at(i) = max(bit.at(i), x);
      i += i & -i;
    }
  }

  void reset() {
    bit.assign(MAXN+1, 0LL);
  }

  // get max bit[j] (0 <= j <= i)
  ll getmax(int i) {
    ll s = 0;
    while (i>0) {
      s = max(bit.at(i), s);
      i -= i & -i;
    }
    return s;
  }
} B;
