#include<vector>

class BitSum {
    vector<long long> bit;
    int MAXN;

    // return bit[1] + ... + bit[i]
public: long long sum(int i) {
      long long s = 0;
      while (i > 0) {
        s += bit[i];
        i -= i & -i;
      }
      return s;
    }

    // bit[i] += x
    BitSum(int n) {
      MAXN = n;
      bit.resize(n+1);
    }

public: void add(int i, long long x) {
      while (i <= MAXN) {
        bit[i] += x;
        i += i & -i;
      }
    }

public: void reset() {
      for(int i=0; i<=MAXN; i++) {
        bit.at(i) = 0;
      }
    }

    // return the smallest i where sum(i) >= val
    // If sum(MAXN) < val, return INT_MAX
public: int lower_bound(long long val) {
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
};
