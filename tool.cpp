// Miscellaneous tools

// greatest common divisor
long long gcd(long long a, long long b) {
  long long r = 1;
  while (r != 0) {
    r = a%b; a = b; b = r;
  }
  return a;
}

// return a^n (mod mod)
long long mod_pow(long long a, long long n, long long mod) {
  long long res = 1;
  while(n > 0) {
    if (n & 1) res = res * a % mod;
    a = a * a % mod; n >>= 1;
  }
  return res;
}