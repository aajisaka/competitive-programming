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

void swap(int &a, int &b) {
  int tmp = b;
  b = a;
  a = tmp;
}