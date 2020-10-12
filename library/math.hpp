#pragma once
#include "internal/internal_math.hpp"
#include <algorithm>
#include <cassert>
#include <tuple>
#include <vector>
#include <chrono>
#include <random>
#include <utility>

long long pow_mod(long long x, long long n, int m) {
  assert(0 <= n && 1 <= m);
  if (m == 1) return 0;
  internal::barrett bt((unsigned int)(m));
  unsigned int r = 1, y = (unsigned int)(internal::safe_mod(x, m));
  while (n) {
    if (n & 1) r = bt.mul(r, y);
    y = bt.mul(y, y);
    n >>= 1;
  }
  return r;
}

long long inv_mod(long long x, long long m) {
  assert(1 <= m);
  auto z = internal::inv_gcd(x, m);
  assert(z.first == 1);
  return z.second;
}

long long norm_mod(long long a, long long p){
  a%=p;
  if(a<0)a+=p;
  return a;
}

// p: odd (not necessarily prime)
long long jacobi(long long a, long long p) {
  a = norm_mod(a, p);
  auto neg = [](long long x) { return x % 2 ? -1 : 1; };
  if (a == 0) return p == 1;
  else if (a % 2) return neg(((p - 1) & (a - 1)) >> 1) * jacobi(p % a, a);
  else return neg(((p & 15) * (p & 15) - 1) / 8) * jacobi(a / 2, p);
}

long long rand_int(long long l, long long r) { //[l, r]
#ifdef LOCAL
  static std::mt19937_64 gen;
#else
  static std::mt19937_64 gen(std::chrono::steady_clock::now().time_since_epoch().count());
#endif
  return std::uniform_int_distribution<>(l, r)(gen);
}

// p: prime
// 0 <= a < p
// returns minimum solution
// returns -1 if not exist
long long sqrt_mod(long long a, long long p) {
  assert(0 <= a);
  assert(a < p);
  if (p == 2)return a % 2;
  if (a == 0)return 0;
  if (jacobi(a, p) == -1)return -1;
  long long b, c;
  do {
    b = rand_int(0, p - 1);
    c = norm_mod(b * b - a, p);
  } while (jacobi(c, p) != -1);
  auto mul = [&](std::pair<long long, long long> x, std::pair<long long, long long> y) {
      return std::pair<int, int>(norm_mod(x.first * y.first + x.second * y.second % p * c, p),
                                 norm_mod(x.first * y.second + x.second * y.first, p));
  };
  std::pair<long long, long long> x(b, 1), cur(1, 0);
  long long n = (p + 1) / 2;
  while (n) {
    if (n & 1)cur = mul(cur, x);
    x = mul(x, x);
    n >>= 1;
  }
  assert(cur.second == 0);
  return std::min(cur.first, p - cur.first);
}

// (rem, mod)
std::pair<long long, long long> crt(const std::vector<long long>& r,
                                    const std::vector<long long>& m) {
  assert(r.size() == m.size());
  int n = int(r.size());
  // Contracts: 0 <= r0 < m0
  long long r0 = 0, m0 = 1;
  for (int i = 0; i < n; i++) {
    assert(1 <= m[i]);
    long long r1 = internal::safe_mod(r[i], m[i]), m1 = m[i];
    if (m0 < m1) {
      std::swap(r0, r1);
      std::swap(m0, m1);
    }
    if (m0 % m1 == 0) {
      if (r0 % m1 != r1) return {0, 0};
      continue;
    }
    // assume: m0 > m1, lcm(m0, m1) >= 2 * max(m0, m1)

    // (r0, m0), (r1, m1) -> (r2, m2 = lcm(m0, m1));
    // r2 % m0 = r0
    // r2 % m1 = r1
    // -> (r0 + x*m0) % m1 = r1
    // -> x*u0*g % (u1*g) = (r1 - r0) (u0*g = m0, u1*g = m1)
    // -> x = (r1 - r0) / g * inv(u0) (mod u1)

    // im = inv(u0) (mod u1) (0 <= im < u1)
    long long g, im;
    std::tie(g, im) = internal::inv_gcd(m0, m1);

    long long u1 = (m1 / g);
    // |r1 - r0| < (m0 + m1) <= lcm(m0, m1)
    if ((r1 - r0) % g) return {0, 0};

    // u1 * u1 <= m1 * m1 / g / g <= m0 * m1 / g = lcm(m0, m1)
    long long x = (r1 - r0) / g % u1 * im % u1;

    // |r0| + |m0 * x|
    // < m0 + m0 * (u1 - 1)
    // = m0 + m0 * m1 / g - m0
    // = lcm(m0, m1)
    r0 += x * m0;
    m0 *= u1;  // -> lcm(m0, m1)
    if (r0 < 0) r0 += m0;
  }
  return {r0, m0};
}
