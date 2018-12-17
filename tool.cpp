// Miscellaneous tools

// greatest common divisor
long long gcd(long long a, long long b) {
  long long r = 1;
  while (r != 0) {
    r = a%b;
    a = b;
    b = r;
  }
  return a;
}

// return a^x (mod mod)
long long mod_pow(long long a, long long x, long long mod) {
  long long res = 1;
  while(x > 0) {
    if (x & 1) {
      res = res * a % mod;
    }
    res = res * res % mod;
    x >>= 1;
  }
  return res;
}