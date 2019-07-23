#include<vector>

using namespace std;
using ll = long long;

//constexpr ll mod = 998244353;
constexpr ll mod = 1e9+7;
constexpr int MAXN = 200000;

vector<ll> fact(MAXN+1);

void init() {
  fact[0] = 1;
  for(int i=1; i<=MAXN; i++) fact[i] = fact[i-1]*i%mod;
}

int extgcd(int a, int b, int &x, int &y) {
  int d = a;
  if (b != 0) {
    d = extgcd(b, a%b, y, x); y -= (a/b)*x;
  } else {
    x = 1; y = 0;
  }
  return d;
}

// m is a large prime integer. Usually 1000000007 is used.
int mod_inverse(int a, int m) {
  int x, y; extgcd(a, m, x, y);
  return (m + x%m)%m;
}

// nCr
ll comb(int n, int r) {
  if (n < r || n < 0 || r < 0) return 0;
  ll ret = fact[n];
  ll nr = mod_inverse(fact[r]*fact[n-r]%mod, mod);
  return ret*nr%mod;
}