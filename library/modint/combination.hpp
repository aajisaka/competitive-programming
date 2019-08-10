template<ll mod=mod17>
class combination {
    // factorial
    public: vector<mint<mod>> fact;
    public: vector<mint<mod>> inv;

    combination(int n) {
      fact.resize(n + 1);
      inv.resize(n + 1);
      fact[0] = 1;
      for (int i = 1; i <= n; i++) fact[i] = fact[i - 1] * i;
      inv[n] = mint<mod>(1) / fact[n];
      for (int i = n - 1; i >= 0; i--) inv[i] = inv[i + 1] * (i + 1);
    }

    // nCr
    public: mint<mod> get(int n, int r) {
      if (n < r || n < 0 || r < 0) return 0;
      return fact[n]*inv[r]*inv[n-r];
    }
    // nPr
    public: mint<mod> p(int n, int r) {
      if (n < r || n < 0) return 0;
      return fact[n]*inv[n-r];
    }
};