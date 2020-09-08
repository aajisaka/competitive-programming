#pragma once
#include "../common.hpp"

class FenwickTree {
    std::vector<long long> data;
    int MAXN;

public: long long sum(int r) {
      long long s = 0;
      while (r > 0) {
        s += data[r-1];
        r -= r & -r;
      }
      return s;
    }

public: long long sum(int l, int r) {
      return sum(r) - sum(l);
    }

    FenwickTree(int n) {
      MAXN = n;
      data.resize(n);
    }

public: void add(int p, long long x) {
      p++;
      while (p <= MAXN) {
        data[p-1] += x;
        p += p & -p;
      }
    }

public: void reset() {
      for(int i=0; i<MAXN; i++) {
        data[i] = 0;
      }
    }

    // TODO: This function is experimental and not verified.
    // return the smallest i where sum(i) >= val
    // If sum(MAXN) < val, return MAXN
    // This function can only be called if all the data is positive or zero.
public: int lower_bound(const long long val) {
      long long now = 0;
      int ret = -1;
      int cnt = 1;
      for(int k=0; k<30; k++) {
        if (cnt*2 > MAXN) break;
        cnt *= 2;
      }
      while(cnt) {
        if (ret+cnt < MAXN && now+data[ret+cnt] < val) {
          now += data[ret+cnt];
          ret += cnt;
        }
        cnt /= 2;
      }
      return ret+1;
    }
};
