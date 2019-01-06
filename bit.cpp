#include<vector>

const int MAXN = 1000000;
struct {
  vector<long long> bit = vector<long long>(MAXN+1);

  // return bit[0] + bit[1] + ... + bit[i]
  ll sum(int i) {
    ll s = 0;
    while (i > 0) {
      s += bit.at(i);
      i -= i & -i;
    }
    return s;
  }

  // bit[i] += x
  void add(int i, long long x) {
    while (i <= MAXN) {
      bit.at(i) += x;
      i += i & -i;
    }
  }

  void reset() {
    for(int i=0; i<=MAXN; i++) {
      bit.at(i) = 0;
    }
  }

  // return the smallest i where sum(i) >= val
  // If sum(MAXN) < val, return INT_MAX
  int lower_bound(long long val) {
    int min = 0;
    int max = MAXN;
    if (sum(max) < val) return INT_MAX;
    if (sum(0) >= val) return 0;
    while(min + 1 < max) {
      int now = (min+max)/2;
      if (sum(now) >= val) {
        max = now;
      } else {
        min = now;
      }
    }
    return max;
  }
}