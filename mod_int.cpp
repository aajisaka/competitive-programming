#include<iostream>

using ll = long long;

using namespace std;
constexpr ll mod = 1e9+7;

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
istream& operator>>(istream&i,mint&a){i>>a.x;return i;}
ostream& operator<<(ostream&o,const mint&a){o<<a.x;return o;}

mint mod_pow(mint a, long long x) {
  mint res = 1;
  while(x > 0) {
    if (x & 1) res *= a;
    a *= a; x >>= 1;
  }
  return res;
}

int MAXN = 100000;
vector<mint> fact(MAXN+1);

void init() {
  fact[0] = 1;
  for(int i=1; i<=MAXN; i++) fact[i] = fact[i-1]*i;
}

// nCr
mint comb(int n, int r) {
  if (n < r || n < 0 || r < 0) return 0;
  return fact[n]/(fact[r]*fact[n-r]);
}