// Matrix library

template<ll mod=mod17>
struct matrix {
    // return a * b where a and b are n * n matrix
    vector<mint<mod>> mat_mul(const vector<mint<mod>>& a, const vector<mint<mod>>& b, int n) {
      vector<mint<mod>> ret(n*n);
      rep(i, n) rep(j, n) rep(k, n) ret[i*n+j] += a[i*n+k]*b[k*n+j];
      return ret;
    }

    // return identity matrix of size n * n
    vector<mint<mod>> id_mat(int n) {
      vector<mint<mod>> ret(n*n);
      rep(i, n) ret[i*n+i] = 1;
      return ret;
    }

    // return a^x where a is n * n matrix
    // a is changed, so do not use &a
    vector<mint<mod>> mat_pow(vector<mint<mod>> a, unsigned long long x, int n) {
      vector<mint<mod>> ret = id_mat(n);
      while(x>0) {
        if (x&1) ret = mat_mul(ret, a, n);
        a = mat_mul(a, a, n); x>>=1;
      }
      return ret;
    }
};