// Miscellaneous tools

// greatest common divisor
long gcd(long a, long b) {
  long r = 1;
  while (r != 0) {
    r = a%b;
    a = b;
    b = r;
  }
  return a;
}