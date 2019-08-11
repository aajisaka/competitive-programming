constexpr ll mod17 = 1e9+7;
constexpr ll mod19 = 1e9+9;
constexpr ll mod9 = 998244353;
ll mod = mod17;

// Mod int library
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

template<typename T>
T mod_pow(T a, ll x) {
  T res = 1;
  while(x > 0) {
    if (x & 1) res *= a;
    a *= a; x >>= 1;
  }
  return res;
}