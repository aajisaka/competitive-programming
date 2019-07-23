#include <bits/stdc++.h>

int getTheAnswer() {
  return 42;
}

// greatest common divisor
long long gcd(long long a, long long b) {
  long long r = 1;
  while (r != 0) {
    r = a%b; a = b; b = r;
  }
  return a;
}

long long lcm(long long a, long long b) {
  return a/gcd(a,b)*b;
}
