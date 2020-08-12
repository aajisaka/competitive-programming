constexpr ll mod17 = 1e9+7;
constexpr ll mod19 = 1e9+9;
constexpr ll mod9 = 998244353;
ll mod = mod17;

// Mod int libraries
template<typename T>
T mod_pow(T a, ll x) {
  T res = 1;
  while(x > 0) {
    if (x & 1) res *= a;
    a *= a; x >>= 1;
  }
  return res;
}

// Mint32
unordered_map<ll, ll> minvmap;
ll minv(ll a, ll m) {
  auto k = a; auto p = minvmap[a]; if (p != 0) return p;
  ll b = m, u = 1, v = 0;
  while (b) { ll t = a/b; swap(a -= t*b, b); swap(u -= t*v, v); }
  p = (u%m+m)%m; minvmap[k] = p; return p;
}

struct mint {
  ll x;
  mint():x(0){}
  mint(ll x):x((x%mod+mod)%mod){}
  mint& fix() { x = (x%mod+mod)%mod; return *this;}
  mint operator-() const { return mint(0) - *this;}
  mint& operator+=(const mint& a){ if((x+=a.x)>=mod) x-=mod; return *this;}
  mint& operator-=(const mint& a){ if((x+=mod-a.x)>=mod) x-=mod; return *this;}
  mint& operator*=(const mint& a){ (x*=a.x)%=mod; return *this;}
  mint& operator/=(const mint& a){ (x*=minv(a.x, mod))%=mod; return *this; }
  mint operator+(const mint& a)const{ return mint(*this) += a;}
  mint operator-(const mint& a)const{ return mint(*this) -= a;}
  mint operator*(const mint& a)const{ return mint(*this) *= a;}
  mint operator/(const mint& a)const{ return mint(*this) /= a;}
  bool operator<(const mint& a)const{ return x < a.x;}
  bool operator==(const mint& a)const{ return x == a.x;}
};

// Mint64
struct mint64 {
    ull x;
    static ull mod, inv, r2;
    mint64(): x(0){}
    mint64(ull x): x(init(x)) {}
    static ull init(ull x) { return reduce(__uint128_t(x)*r2);}
    static void set_mod(ull m) {
      mod = inv = m;
      for(int i=0; i<5; i++) inv *= 2 - inv*m;
      r2 = -__uint128_t(m)%m;
    }
    static ull reduce(__uint128_t x) {
      ull y = ull(x >> 64) - ull((__uint128_t(ull(x)*inv)*mod)>>64);
      return ll(y) < 0 ? y+mod : y;
    }
    mint64& operator+=(mint64& a) { x+=a.x-mod; if(ll(x)<0) x+=mod; return *this; }
    mint64 operator+(mint64& a) const{ return mint64(*this)+=a; }
    mint64& operator*=(mint64& a) { x=reduce(__uint128_t(x)*a.x); return *this; }
    mint64 operator*(mint64& a) const { return mint64(*this)*=a; }
};

ull mint64::mod, mint64::inv, mint64::r2;

// Verify: https://yukicoder.me/submissions/472580
struct Miller {
    const vector<ull> v = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
    bool suspect(ull a, ull s, ull d, ull n) {
      if (mint64::mod != n) mint64::set_mod(n);
      mint64 one = 1, minusone = n-1, ma = a;
      auto x = mod_pow(ma, d);
      if (x.x == one.x) return true;
      for(ull r = 0; r < s; r++) {
        if (x.x == minusone.x) return true;
        x = x * x;
      }
      return false;
    }

    // check if n is prime
    bool check(ull n) {
      if (n < 2 || (n > 2 && n % 2 == 0)) return false;
      ull d = n - 1;
      ull s = 0;
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

class combination {
    // factorial
    public: std::vector<mint> fact;
    public: std::vector<mint> inv;

    combination(int n) {
      fact.resize(n + 1);
      inv.resize(n + 1);
      fact[0] = 1;
      for (int i = 1; i <= n; i++) {
        fact[i] = fact[i - 1] * i;
      }
      inv[n] = mint(1) / fact[n];
      for (int i = n - 1; i >= 0; i--) {
        inv[i] = inv[i + 1] * (i + 1);
      }
    }

    // nCr
    public: mint get(int n, int r) {
      if (n < r || n < 0 || r < 0) return 0;
      return fact[n]*inv[r]*inv[n-r];
    }
    // nPr
    public: mint p(int n, int r) {
      if (n < r || n < 0) return 0;
      return fact[n]*inv[n-r];
    }
};
