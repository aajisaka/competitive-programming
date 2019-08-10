// Matrix library
template<typename T>
T mat_mul(const T& a, const T& b, int n) {
  T ret(n*n);
  for(int i=0; i<n; i++) {
    for(int j=0; j<n; j++) {
      for(int k=0; k<n; k++) {
        ret[i*n+j] += a[i*n+k]*b[k*n+j];
      }
    }
  }
  return ret;
}

// return a^x where a is n * n matrix
// a is changed, so do not use &a
template<typename T>
T mat_pow(T a, unsigned long long x, int n) {
  T ret(n*n);
  for(int i=0; i<n; i++) ret[i*n+i] = 1;
  while(x>0) {
    if (x&1) ret = mat_mul(ret, a, n);
    a = mat_mul(a, a, n); x>>=1;
  }
  return ret;
}