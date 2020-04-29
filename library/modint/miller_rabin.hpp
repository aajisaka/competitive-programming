// TODO: Create and use 64bit mint class to avoid % function. This speed up to ~10x.
// Verify: https://yukicoder.me/submissions/472560
struct Miller {
    const vector<unsigned long long> v = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
    unsigned long long modpow(unsigned long long x, unsigned long long k, unsigned long long m){
      unsigned long long res = 1;
      while(k > 0){
        if(k&1){
          res = __uint128_t(res) * x % m;
        }
        k /= 2;
        x = __uint128_t(x) * x % m;
      }
      return res;
    }
    bool suspect(unsigned long long a, unsigned long long s, unsigned long long d, unsigned long long n) {
      unsigned long long x = modpow(a, d, n);
      if (x == 1) return true;
      for(int r = 0; r < s; r++) {
        if (x == n-1) return true;
        x = __uint128_t(x) * x % n;
      }
      return false;
    }

    // check if n is prime
    bool check(unsigned long long n ) {
      if (n < 2 || (n > 2 && n % 2 == 0)) return false;
      unsigned long long d = n - 1;
      unsigned long long s = 0;
      while (!(d & 1)) {
        d >>= 1;
        s++;
      }
      for (auto a: v) {
        if (a >= n) break;
        if (!suspect(a, s, d, n)) return false;
      }
      return true;
    }
};
