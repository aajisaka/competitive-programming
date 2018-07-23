int extgcd(int a, int b, int &x, int &y) {
  int d = a;
  if (b != 0) {
    d = extgcd(b, a%b, y, x);
    y -= (a/b)*x;
  } else {
    x = 1;
    y = 0;
  }
  return d;
}

// m is a large prime integer. Usually 1000000007 is used.
int mod_inverse(int a, int m) {
  int x, y;
  extgcd(a, m, x, y);
  return (m + x%m)%m;
}