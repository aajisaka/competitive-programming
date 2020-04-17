// Fast Walsh-Hadamard transform
// Original: https://kazuma8128.hatenablog.com/entry/2018/05/31/144519

// Get C[k] = Sum(A[i]*B[j]) (i^j=k) by O(nlogn)
// n must be 2^p (p: non-negative integer)
// fwt_xor(A); fwt_xor(B);
// rep(i, n) C[i] = A[i]*B[i];
// ifwt_xor(C);
template <typename T>
void fwt_xor(vector<T>& f) {
  int n = f.size();
  for (int i = 1; i < n; i <<= 1) {
    for (int j = 0; j < n; j++) {
      if ((j & i) == 0) {
        T x = f[j], y = f[j | i];
        f[j] = x + y, f[j | i] = x - y;
      }
    }
  }
}
template <typename T>
void ifwt_xor(vector<T>& f) {
  int n = f.size();
  for (int i = 1; i < n; i <<= 1) {
    for (int j = 0; j < n; j++) {
      if ((j & i) == 0) {
        T x = f[j], y = f[j | i];
        f[j] = (x + y) / 2, f[j | i] = (x - y) / 2;
      }
    }
  }
}

// Get C[k] = Sum(A[i]*B[j]) (i|j=k) by O(nlogn)
// n must be 2^p (p: non-negative integer)
// fwt_or(A); fwt_or(B);
// rep(i, n) C[i] = A[i]*B[i];
// ifwt_or(C);
template <typename T>
void fwt_or(vector<T>& f) {
  int n = f.size();
  for (int i = 1; i < n; i <<= 1) {
    for (int j = 0; j < n; j++) {
      if ((j & i) == 0) {
        f[j | i] += f[j];
      }
    }
  }
}
template <typename T>
void ifwt_or(vector<T>& f) {
  int n = f.size();
  for (int i = 1; i < n; i <<= 1) {
    for (int j = 0; j < n; j++) {
      if ((j & i) == 0) {
        f[j | i] -= f[j];
      }
    }
  }
}

// Get C[k] = Sum(A[i]*B[j]) (i&j=k) by O(nlogn)
// n must be 2^p (p: non-negative integer)
// fwt_and(A); fwt_and(B);
// rep(i, n) C[i] = A[i]*B[i];
// ifwt_and(C);
template <typename T>
void fwt_and(vector<T>& f) {
  int n = f.size();
  for (int i = 1; i < n; i <<= 1) {
    for (int j = 0; j < n; j++) {
      if ((j & i) == 0) {
        f[j] += f[j | i];
      }
    }
  }
}
template <typename T>
void ifwt_and(vector<T>& f) {
  int n = f.size();
  for (int i = 1; i < n; i <<= 1) {
    for (int j = 0; j < n; j++) {
      if ((j & i) == 0) {
        f[j] -= f[j | i];
      }
    }
  }
}
