#pragma once
#include <algorithm>
#include <array>
#include <cassert>
#include <type_traits>
#include <vector>
#include "../internal/internal_bit.hpp"
#include "../internal/internal_math.hpp"
#include "../modint.hpp"

namespace internal {
    template<class mint, internal::is_static_modint_t<mint> * = nullptr>
    void butterfly(std::vector<mint> &a) {
      static constexpr int g = internal::primitive_root<mint::mod()>;
      int n = int(a.size());
      int h = internal::ceil_pow2(n);

      static bool first = true;
      static mint sum_e[30];  // sum_e[i] = ies[0] * ... * ies[i - 1] * es[i]
      if (first) {
        first = false;
        mint es[30], ies[30];  // es[i]^(2^(2+i)) == 1
        int cnt2 = bsf(mint::mod() - 1);
        mint e = mint(g).pow((mint::mod() - 1) >> cnt2), ie = e.inv();
        for (int i = cnt2; i >= 2; i--) {
          // e^(2^i) == 1
          es[i - 2] = e;
          ies[i - 2] = ie;
          e *= e;
          ie *= ie;
        }
        mint now = 1;
        for (int i = 0; i < cnt2 - 2; i++) {
          sum_e[i] = es[i] * now;
          now *= ies[i];
        }
      }
      for (int ph = 1; ph <= h; ph++) {
        int w = 1 << (ph - 1), p = 1 << (h - ph);
        mint now = 1;
        for (int s = 0; s < w; s++) {
          int offset = s << (h - ph + 1);
          for (int i = 0; i < p; i++) {
            auto l = a[i + offset];
            auto r = a[i + offset + p] * now;
            a[i + offset] = l + r;
            a[i + offset + p] = l - r;
          }
          now *= sum_e[bsf(~(unsigned int) (s))];
        }
      }
    }

    template<class mint, internal::is_static_modint_t<mint> * = nullptr>
    void butterfly_inv(std::vector<mint> &a) {
      static constexpr int g = internal::primitive_root<mint::mod()>;
      int n = int(a.size());
      int h = internal::ceil_pow2(n);

      static bool first = true;
      static mint sum_ie[30];  // sum_ie[i] = es[0] * ... * es[i - 1] * ies[i]
      if (first) {
        first = false;
        mint es[30], ies[30];  // es[i]^(2^(2+i)) == 1
        int cnt2 = bsf(mint::mod() - 1);
        mint e = mint(g).pow((mint::mod() - 1) >> cnt2), ie = e.inv();
        for (int i = cnt2; i >= 2; i--) {
          // e^(2^i) == 1
          es[i - 2] = e;
          ies[i - 2] = ie;
          e *= e;
          ie *= ie;
        }
        mint now = 1;
        for (int i = 0; i < cnt2 - 2; i++) {
          sum_ie[i] = ies[i] * now;
          now *= es[i];
        }
      }

      for (int ph = h; ph >= 1; ph--) {
        int w = 1 << (ph - 1), p = 1 << (h - ph);
        mint inow = 1;
        for (int s = 0; s < w; s++) {
          int offset = s << (h - ph + 1);
          for (int i = 0; i < p; i++) {
            auto l = a[i + offset];
            auto r = a[i + offset + p];
            a[i + offset] = l + r;
            a[i + offset + p] =
                (unsigned long long) (mint::mod() + l.val() - r.val()) *
                inow.val();
          }
          inow *= sum_ie[bsf(~(unsigned int) (s))];
        }
      }
    }
}

template<class mint, internal::is_static_modint_t<mint> * = nullptr>
std::vector<mint> convolution(std::vector<mint> a, std::vector<mint> b) {
  int n = int(a.size()), m = int(b.size());
  if (!n || !m) return {};
  if (std::min(n, m) <= 60) {
    if (n < m) {
      std::swap(n, m);
      std::swap(a, b);
    }
    std::vector<mint> ans(n + m - 1);
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        ans[i + j] += a[i] * b[j];
      }
    }
    return ans;
  }
  int z = 1 << internal::ceil_pow2(n + m - 1);
  a.resize(z);
  internal::butterfly(a);
  b.resize(z);
  internal::butterfly(b);
  for (int i = 0; i < z; i++) {
    a[i] *= b[i];
  }
  internal::butterfly_inv(a);
  a.resize(n + m - 1);
  mint iz = mint(z).inv();
  for (int i = 0; i < n + m - 1; i++) a[i] *= iz;
  return a;
}

template <unsigned int mod = 998244353,
    class T,
    std::enable_if_t<internal::is_integral<T>::value>* = nullptr>
std::vector<T> convolution(const std::vector<T>& a, const std::vector<T>& b) {
  int n = int(a.size()), m = int(b.size());
  if (!n || !m) return {};

  using mint = static_modint<mod>;
  std::vector<mint> a2(n), b2(m);
  for (int i = 0; i < n; i++) {
    a2[i] = mint(a[i]);
  }
  for (int i = 0; i < m; i++) {
    b2[i] = mint(b[i]);
  }
  auto c2 = convolution(move(a2), move(b2));
  std::vector<T> c(n + m - 1);
  for (int i = 0; i < n + m - 1; i++) {
    c[i] = c2[i].val();
  }
  return c;
}

std::vector<long long> convolution_ll(const std::vector<long long>& a,
                                      const std::vector<long long>& b) {
  int n = int(a.size()), m = int(b.size());
  if (!n || !m) return {};

  static constexpr unsigned long long MOD1 = 754974721;  // 2^24
  static constexpr unsigned long long MOD2 = 167772161;  // 2^25
  static constexpr unsigned long long MOD3 = 469762049;  // 2^26
  static constexpr unsigned long long M2M3 = MOD2 * MOD3;
  static constexpr unsigned long long M1M3 = MOD1 * MOD3;
  static constexpr unsigned long long M1M2 = MOD1 * MOD2;
  static constexpr unsigned long long M1M2M3 = MOD1 * MOD2 * MOD3;

  static constexpr unsigned long long i1 =
      internal::inv_gcd(MOD2 * MOD3, MOD1).second;
  static constexpr unsigned long long i2 =
      internal::inv_gcd(MOD1 * MOD3, MOD2).second;
  static constexpr unsigned long long i3 =
      internal::inv_gcd(MOD1 * MOD2, MOD3).second;

  auto c1 = convolution<MOD1>(a, b);
  auto c2 = convolution<MOD2>(a, b);
  auto c3 = convolution<MOD3>(a, b);

  std::vector<long long> c(n + m - 1);
  for (int i = 0; i < n + m - 1; i++) {
    unsigned long long x = 0;
    x += (c1[i] * i1) % MOD1 * M2M3;
    x += (c2[i] * i2) % MOD2 * M1M3;
    x += (c3[i] * i3) % MOD3 * M1M2;
    // B = 2^63, -B <= x, r(real value) < B
    // (x, x - M, x - 2M, or x - 3M) = r (mod 2B)
    // r = c1[i] (mod MOD1)
    // focus on MOD1
    // r = x, x - M', x - 2M', x - 3M' (M' = M % 2^64) (mod 2B)
    // r = x,
    //     x - M' + (0 or 2B),
    //     x - 2M' + (0, 2B or 4B),
    //     x - 3M' + (0, 2B, 4B or 6B) (without mod!)
    // (r - x) = 0, (0)
    //           - M' + (0 or 2B), (1)
    //           -2M' + (0 or 2B or 4B), (2)
    //           -3M' + (0 or 2B or 4B or 6B) (3) (mod MOD1)
    // we checked that
    //   ((1) mod MOD1) mod 5 = 2
    //   ((2) mod MOD1) mod 5 = 3
    //   ((3) mod MOD1) mod 5 = 4
    long long diff =
        c1[i] - internal::safe_mod((long long)(x), (long long)(MOD1));
    if (diff < 0) diff += MOD1;
    static constexpr unsigned long long offset[5] = {
        0, 0, M1M2M3, 2 * M1M2M3, 3 * M1M2M3};
    x -= offset[diff % 5];
    c[i] = x;
  }

  return c;
}

template<class mint, internal::is_static_modint_t<mint> * = nullptr>
struct dual_vec {
    std::vector<mint> v;

    void resize(int sz) {
      v.resize(sz);
    }
};

template<class mint, internal::is_static_modint_t<mint> * = nullptr>
dual_vec<mint> mfft(const std::vector<mint> &a, int sz) {
  dual_vec<mint> fa{a};
  fa.resize(sz);
  internal::butterfly(fa.v);
  return fa;
}

template<class mint, internal::is_static_modint_t<mint> * = nullptr>
dual_vec<mint> operator*(dual_vec<mint> a, const dual_vec<mint> &b) {
  for (int i = 0; i < (int) a.v.size(); i++) {
    a.v[i] *= b.v[i];
  }
  return a;
}

template<class mint, internal::is_static_modint_t<mint> * = nullptr>
std::vector<mint> ifft(dual_vec<mint> fa, int n) {
  internal::butterfly_inv(fa.v);
  mint iz = mint(fa.v.size()).inv();
  for (int i = 0; i < fa.v.size(); i++) fa.v[i] *= iz;
  fa.resize(n);
  return fa.v;
}

template<class T>
vector<T> derivative(const vector<T> &a) {
  vector<T> res(max((int) a.size() - 1, 0));
  for (int i = 0; i < (int) res.size(); ++i) res[i] = (i + 1) * a[i + 1];
  return res;
}

template<class T>
vector<T> primitive(const vector<T> &a) {
  vector<T> res(a.size() + 1);
  for (int i = 1; i < (int) res.size(); ++i) res[i] = a[i - 1] / i;
  return res;
}

template<class mint, internal::is_static_modint_t<mint> * = nullptr>
std::vector<mint> inverse(const std::vector<mint> &a) {
  assert(a.size());
  assert(a[0].val() != 0);
  std::vector<mint> b{1 / a[0]};
  for (int m = 1; m < (int) a.size(); m *= 2) {
    std::vector<mint> x(begin(a), begin(a) + std::min<int>(a.size(), 2 * m));
    dual_vec<mint> fb = mfft(b, 2 * m);
    x = ifft(mfft(x, 2 * m) * fb, 2 * m);
    fill(begin(x), begin(x) + m, 0);
    x = ifft(mfft(x, 2 * m) * fb, 2 * m);
    for (auto &e: x) e = -e;
    b.insert(end(b), begin(x) + m, end(x));
  }
  return {begin(b), begin(b) + a.size()};
}

template<class mint, internal::is_static_modint_t<mint> * = nullptr>
std::vector<mint> exponent(const std::vector<mint> &a) {
  assert(a.empty() or a[0].val() == 0);
  std::vector<mint> b{1, 1 < a.size() ? a[1] : 0};
  std::vector<mint> c{1};
  dual_vec<mint> half_fc;
  auto fc = mfft(c, 2);
  for (int m = 2; m < (int) a.size(); m *= 2) {
    auto fb = mfft(b, 2 * m);
    auto half_fb = fb;
    half_fb.resize(m);
    half_fc = fc;
    auto z = ifft(half_fb * half_fc, m);
    fill(begin(z), begin(z) + m / 2, 0);
    z = ifft(mfft(z, m) * half_fc, m);
    for (auto &e: z) e = -e;
    c.insert(end(c), begin(z) + m / 2, end(z));
    fc = mfft(c, 2 * m);
    std::vector<mint> x(begin(a), begin(a) + min<int>(a.size(), m));
    x = derivative(x);
    x.push_back(0);
    auto fx = mfft(x, m);
    x = ifft(fx * half_fb, m);
    std::vector<mint> db = derivative(b);
    x.resize(max(x.size(), db.size()));
    for (int i = 0; i < (int) db.size(); i++) x[i] -= db[i];
    x.resize(2 * m);
    for (int i = 0; i < m - 1; i++) x[m + i] = x[i], x[i] = 0;
    x = ifft(mfft(x, 2 * m) * fc, 2 * m);
    x = primitive(x);
    x.pop_back();
    for (int i = m; i < min<int>(a.size(), 2 * m); i++) x[i] += a[i];
    fill(begin(x), begin(x) + m, 0);
    x = ifft(mfft(x, 2 * m) * fb, 2 * m);
    b.insert(end(b), begin(x) + m, end(x));
  }
  return {begin(b), begin(b) + a.size()};
}

template<class mint, internal::is_static_modint_t<mint> * = nullptr>
std::vector<mint> logarithm(const std::vector<mint> &a) {
  assert(not a.empty() and a[0] == 1);
  auto res = primitive(convolution(derivative(a), inverse(a)));
  return {begin(res), begin(res) + a.size()};
}

template<class mint, internal::is_static_modint_t<mint> * = nullptr>
std::vector<mint> power(std::vector<mint> a, long long m) {
  int n = size(a);
  int tz = 0;
  while (tz < n and a[tz] == 0) tz++;
  if (n == 0 or (tz and m >= (n + tz - 1) / tz)) return vector<mint>(n);
  a.erase(begin(a), begin(a) + min<int>(a.size(), tz));
  auto a0 = a[0];
  a = convolution(a, vector<mint>{1 / a0});
  a = exponent(convolution(logarithm(a), vector<mint>{m}));
  a = convolution(a, vector<mint>{a0.pow(m)});
  a.insert(begin(a), tz * m, 0);
  return a;
}
