// Miscellaneous tools

// greatest common divisor
long long gcd(long long a, long long b) {
  long long r = 1;
  while (r != 0) {
    r = a%b; a = b; b = r;
  }
  return a;
}

// return a^x (mod mod)
long long mod_pow(long long a, long long x, long long mod) {
  long long res = 1;
  while(x > 0) {
    if (x & 1) res = res * a % mod;
    a = a * a % mod; x >>= 1;
  }
  return res;
}

// return a * b where a and b are n * n matrix
vector<ll> mat_mul(const T& a, const T& b, int n, ll mod) {
  vector<ll> ret(n*n);
  rep(i, n) {
    rep(j, n) {
      rep(k, n) {
        ret[i*n+j] += a[i*n+k]*b[k*n+j];
        ret[i*n+j] %= mod;
      }
    }
  }
  return ret;
}

// return identity matrix of size n * n
vector<ll> id_mat(int n) {
  vector<ll> ret(n*n);
  rep(i, n) {
    ret[i*n+i] = 1;
  }
  return ret;
}

// return a^x where a is n * n matrix
// a is changed, so do not use &a
vector<ll> mat_pow(vector<ll> a, int x, int n, ll mod) {
  vector<ll> res = id_mat(n);
  while(x>0) {
    if (x&1) res = mat_mul(res, a, n, mod);
    a = mat_mul(a, a, n, mod); x>>=1;
  }
  return res;
}