// Original: https://github.com/kirika-comp/articles/blob/pre-releases/pre-seisuuron.pdf

using comp = complex<double>;
void fft(int n, vector<comp>& a, double dir) {
  {
    int i = 0;
    for (int j = 1; j < n - 1; j++) {
      for (int k = n >> 1; k > (i ^= k); k >>= 1);
      if (j < i) swap(a[i], a[j]);
    }
  }
  vector<comp> zeta_pow(n);
  for(int i=0; i<n; i++) {
    double theta = PI/n*i*dir;
    zeta_pow[i] = comp(cos(theta), sin(theta));
  }
  for(int m=1; m<n; m*=2) {
    for(int y=0; y<m; y++) {
      comp fac = zeta_pow[n/m*y];
      for(int x=0; x<n; x+=2*m) {
        int u = x+y;
        int v = x+y+m;
        comp s = a[u]+fac*a[v];
        comp t = a[u]-fac*a[v];
        a[u] = s;
        a[v] = t;
      }
    }
  }
}
template<class T>
vector<comp> convolution(const vector<T> &a, const vector<T> &b) {
  int n = 1;
  while(n<a.size()+b.size()) n*=2;
  vector<comp> a_(n), b_(n);
  rep(i, a.size()) a_[i] = a[i];
  rep(i, b.size()) b_[i] = b[i];
  fft(n, a_, 1);
  fft(n, b_, 1);
  rep(i, n) {
    a_[i] *= b_[i];
  }
  fft(n, a_, -1);
  rep(i, n) {
    a_[i] /= n;
  }
  return a_;
}

/*
 * Get c[i] = a[j] * b[k] s.t. (j+k)%n = i
 *
 * n >= a.size() + b.size()
 * u = max(max(a[i]), max(b[i]))
 * double can be used if n*u*u <= 10^15 (2^53)
 */
vector<ll> integral_convolution(const vector<ll> &a, const vector<ll> &b) {
  vector<comp> ans = convolution(a, b);
  vector<ll> ret(ans.size());
  rep(i, ans.size()) {
    ret[i] = floor(ans[i].real()+0.5);
  }
  return ret;
}
