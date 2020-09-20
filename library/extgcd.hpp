// Returns gcd(a, b)
// Update x and y that satisfies ax + by = gcd(a, b)
long long extGCD(long long a, long long b, long long &x, long long &y) {
  if (b == 0) {
    x = 1;
    y = 0;
    return a;
  }
  long long d = extGCD(b, a%b, y, x);
  y -= a/b * x;
  return d;
}
